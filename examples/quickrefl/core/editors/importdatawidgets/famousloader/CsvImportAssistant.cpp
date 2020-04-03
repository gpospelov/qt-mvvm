// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportAssistant.cpp
//! @brief     Implements class CsvImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvImportAssistant.h"
#include "DataFormatUtils.cpp"
#include "DataSelector.h"
#include "ImportDataInfo.h"
#include "StyleUtils.h"
#include "mainwindow_constants.h"
#include <QFileDialog>
#include <QFormLayout>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QTableWidget>
#include <QVBoxLayout>
#include <algorithm>

CsvImportAssistant::CsvImportAssistant(const QString& file, const bool useGUI, QWidget* parent)
    : m_fileName(file), m_csvFile(nullptr), m_csvArray(), m_separator('\0'), m_intensityColNum(-1),
      m_intensityMultiplier(1.0), m_coordinateColNum(-1), m_coordinateMultiplier(1.0),
      m_firstRow(-1), m_lastRow(-1), m_units(AxesUnits::NBINS), m_dataAvailable(false)
{
    if (!loadCsvFile()) {
        return;
    }

    if (useGUI) {
        runDataSelector(parent);
    } else {
        m_intensityColNum = 0;
        m_coordinateColNum = -1;
        m_units = AxesUnits::NBINS;
        m_firstRow = 0;
        m_lastRow = int(m_csvFile->NumberOfRows() - 1);
        m_dataAvailable = true;
    }
}

void CsvImportAssistant::runDataSelector(QWidget* parent)
{
    DataSelector selector(m_csvArray, parent);
    m_separator = guessSeparator();
    selector.setSeparator(guessSeparator());
    connect(&selector, &DataSelector::separatorChanged, this, [this, &selector](char newSep) {
        if (newSep != m_separator) {
            m_separator = newSep;
            loadCsvFile();
            selector.setDataArray(m_csvArray);
            selector.setSeparator(newSep);
        }
    });

    int res = selector.exec();

    if (res == selector.Accepted) {
        m_intensityColNum = selector.intensityColumn();
        m_intensityMultiplier = selector.intensityMultiplier();
        m_coordinateColNum = selector.coordinateColumn();
        m_coordinateMultiplier = selector.coordinateMultiplier();
        m_units = selector.units();
        m_firstRow = int(selector.firstLine() - 1);
        m_lastRow = int(selector.lastLine() - 1);
        m_rowsToDiscard = selector.rowsToDiscard();
        m_dataAvailable = true;
    } else if (res == selector.Rejected) {
        m_dataAvailable = false;
        return;
    }
}

void CsvImportAssistant::setIntensityColumn(int iCol, double multiplier)
{
    m_intensityColNum = iCol - 1;
    m_intensityMultiplier = multiplier;
}
void CsvImportAssistant::setCoordinateColumn(int iCol, AxesUnits units, double multiplier)
{
    m_coordinateColNum = iCol - 1;
    m_units = units;
    m_coordinateMultiplier = multiplier;
}
void CsvImportAssistant::setFirstRow(int iRow)
{
    m_firstRow = iRow - 1;
}
void CsvImportAssistant::setLastRow(int iRow)
{
    m_lastRow = iRow - 1;
}

bool CsvImportAssistant::loadCsvFile()
{

    try {
        if (m_separator == '\0')
            m_separator = guessSeparator();
        m_csvFile = std::make_unique<CSVFile>(m_fileName.toStdString(), m_separator);
    } catch (...) {
        showErrorMessage("There was a problem opening the file \"" + m_fileName.toStdString()
                         + "\"");
        return false;
    }

    size_t lastRow = m_csvFile->NumberOfRows();

    if (lastRow < 1) {
        CsvImportAssistant::showErrorMessage("The file exist but it seems to be empty");
        return false;
    }

    auto csvArray = m_csvFile->asArray();

    // Automatically ignore empty lines at the end:
    while (QString::fromStdString(accumulate(csvArray[lastRow - 1].begin(),
                                             csvArray[lastRow - 1].end(), std::string("")))
               .trimmed()
           == "") {
        lastRow--;
        if (lastRow < 1) {
            CsvImportAssistant::showErrorMessage("The file exist but it seems to be empty");
            return false;
        }
    }

    // TODO: If separator is white space, ignore consecutive spaces...
    // {
    // }

    csv::DataArray tmp(csvArray.begin(), csvArray.begin() + int(lastRow));
    m_csvArray.swap(tmp);
    removeBlankColumns();
    if (m_separator == ' ')
        removeMultipleWhiteSpaces();

    return true;
}

void CsvImportAssistant::resetAssistant()
{
    resetSelection();
    loadCsvFile();
}

ImportDataInfo CsvImportAssistant::fillData()
{
    // In case a 2d import is needed in the future
    // Use ArrayUtils::Create2dData(vector<vector<double>>)
    // ArrayUtils::Create2d
    std::unique_ptr<OutputData<double>> resultOutputData;
    resultOutputData = std::make_unique<OutputData<double>>();
    std::vector<double> intensityValues;
    std::vector<double> coordinateValues;

    getValuesFromColumns(intensityValues,coordinateValues);

    auto axisName = csv::UnitsLabels[m_units].toStdString();
    PointwiseAxis coordAxis(axisName, coordinateValues);
    resultOutputData->addAxis(coordAxis);
    resultOutputData->setRawDataVector(intensityValues);

    ImportDataInfo result(std::move(resultOutputData), m_units);
    return result;
}

void CsvImportAssistant::getValuesFromColumns(std::vector<double>& intensityValues,
                                              std::vector<double>& coordinateValues)
{
    bool intensityOk = true;
    bool coordinateOk = true;
    auto firstRow = size_t(m_firstRow);
    auto lastRow = size_t(m_lastRow) + 1;
    bool isCoordinateNeeded = m_coordinateColNum > -1;
    double intensityValue = 0.;
    double coordinateValue = 0.;

    for (size_t row = firstRow; row < lastRow; row++) {
        if (std::find(m_rowsToDiscard.begin(), m_rowsToDiscard.end(), int(row))
            == m_rowsToDiscard.end()) {
            // Intensity Values:
            QString intensityText =
                QString::fromStdString(m_csvArray[row][size_t(m_intensityColNum)]);
            intensityValue = intensityText.toDouble(&intensityOk);

            // Coordinate Values:
            if (isCoordinateNeeded) {
                QString coordinateText =
                    QString::fromStdString(m_csvArray[row][size_t(m_coordinateColNum)]);
                coordinateValue = coordinateText.toDouble(&coordinateOk);
            } else {
                coordinateValue = row - firstRow;
            }

            // Add them if they are both ok:
            if (intensityOk && coordinateOk) {
                intensityValues.push_back(m_intensityMultiplier * intensityValue);
                coordinateValues.push_back(m_coordinateMultiplier * coordinateValue);
            }
        }
    }
}

void CsvImportAssistant::removeMultipleWhiteSpaces()
{
    if (m_csvArray.empty())
        return;

    csv::DataArray buffer2d;
    csv::DataRow buffer1d;
    size_t nRows = m_csvArray.size();
    size_t nCols = m_csvArray[0].size();
    size_t newNcols = 0;

    for (size_t i = 0; i < nRows; i++) {
        buffer1d.clear();
        for (size_t j = 0; j < nCols; j++) {
            QString text = QString::fromStdString(m_csvArray[i][j]).trimmed();
            if (text != "")
                buffer1d.push_back(text.toStdString());
        }
        newNcols = std::max(buffer1d.size(), newNcols);
        buffer2d.push_back(buffer1d);
    }

    if (buffer2d.empty()) {
        m_csvArray.clear();
        return;
    }

    for (size_t i = 0; i < nRows; i++)
        while (buffer2d[i].size() < newNcols)
            buffer2d[i].push_back("");

    // now buffer2d has the original array, without empty cells
    nRows = buffer2d.size();
    nCols = buffer2d[0].size();

    m_csvArray.swap(buffer2d);
}

void CsvImportAssistant::removeBlankColumns()
{

    if (m_csvArray.empty())
        return;

    csv::DataArray buffer2d;
    csv::DataRow buffer1d;
    std::vector<int> to_be_removed;

    size_t nRows = m_csvArray.size();
    size_t nCols = m_csvArray[0].size();

    if (!hasEqualLengthLines(m_csvArray)) {
        throw Exceptions::NotImplementedException(
            "All inner vectors should have the same length already.");
    }

    // traverse the array columnwise -- this may be inneficient.
    for (size_t j = 0; j < nCols; j++) {
        buffer1d.clear();
        for (size_t i = 0; i < nRows; i++) {
            buffer1d.push_back(m_csvArray[i][j]);
        }
        if (QString::fromStdString(accumulate(buffer1d.begin(), buffer1d.end(), std::string("")))
                .trimmed()
            == "")
            continue;

        buffer2d.push_back(buffer1d);
    }

    if (buffer2d.empty()) {
        m_csvArray.clear();
        return;
    }

    // now buffer2d has the original array, without blank columns, transposed.
    nCols = buffer2d.size();
    nRows = buffer2d[0].size();

    // Save the modified array --i.e. transpose buffer2d
    m_csvArray.clear();
    for (size_t i = 0; i < nRows; i++) {
        buffer1d.clear();
        for (size_t j = 0; j < nCols; j++) {
            buffer1d.push_back(buffer2d[j][i]);
        }
        m_csvArray.push_back(buffer1d);
    }
}

char CsvImportAssistant::guessSeparator() const
{
    int frequencies[127] = {0};

    // The actual characters that may be realistically
    // used as separators are only a handfull...
    // And this list seems already exagerated.
    std::vector<char> preferredSeparators;
    preferredSeparators.push_back(' ');
    preferredSeparators.push_back(',');
    preferredSeparators.push_back(';');
    preferredSeparators.push_back('|');
    preferredSeparators.push_back(':');
    preferredSeparators.push_back('\t');
    // preferredSeparators.push_back('/');
    // preferredSeparators.push_back('\\');
    // preferredSeparators.push_back('_');
    preferredSeparators.push_back('\'');
    preferredSeparators.push_back('\"');

    // count number of occurences of each char in the file:
    char c;
    std::ifstream is(m_fileName.toStdString());
    while (is.get(c)) {
        if (size_t(c) < 127)
            frequencies[size_t(c)]++;
    }
    is.close();

    // set the guessed separator as the most frequent among the
    // preferred separators. -- Some unavoidable hieararchy is
    // present: characters with lower ascii code are preferred.
    char guessedSep = ' ';
    int freq = 0;
    for (char i = 0; i < 127; i++) {
        if (std::find(preferredSeparators.begin(), preferredSeparators.end(), i)
            != preferredSeparators.end())
            if (frequencies[int(i)] > freq) {
                freq = frequencies[int(i)];
                guessedSep = i;
            }
    }

    // We don't like tabs, as we cannot write them in the GUI.
    // The rest of the CsvImportAssistant and CsvReader should be already aware of this.
    if (guessedSep == '\t')
        guessedSep = ' ';

    return guessedSep;
}

bool CsvImportAssistant::hasEqualLengthLines(csv::DataArray& dataArray)
{
    auto tf = all_of(begin(dataArray), end(dataArray), [dataArray](const csv::DataRow& x) {
        return x.size() == dataArray.front().size();
    });
    return tf;
}

void CsvImportAssistant::showErrorMessage(std::string message)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(message));
    msgBox.setIcon(msgBox.Critical);
    msgBox.exec();
}

void CsvImportAssistant::resetSelection()
{
    m_csvArray.clear();
    m_intensityColNum = -1;
    m_coordinateColNum = -1;
    m_firstRow = -1;
    m_lastRow = -1;
    m_units = AxesUnits::NBINS;
    m_dataAvailable = false;
}
