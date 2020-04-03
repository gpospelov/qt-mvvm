// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportTable.cpp
//! @brief     Implements class CsvImportTable
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvImportTable.h"
#include "ScientificSpinBox.h"

namespace {

ScientificSpinBox* createMultiplierBox(double value = 1.0, bool enabled = false,
                                       QWidget* parent = nullptr)
{
    auto result = new ScientificSpinBox(parent);
    result->setValue(value);
    result->setEnabled(enabled);
    return result;
}
}

CsvImportData::CsvImportData(QObject* parent)
    :QObject(parent)
    , m_data(new csv::DataArray)
    , m_n_header(0)
    , m_n_footer(0)
{}

void CsvImportData::setData(csv::DataArray data)
{
    m_data.reset(new csv::DataArray(std::move(data)));
    m_selected_cols.clear();
    m_n_header = 0;
    m_n_footer = 0;
    m_discarded_rows.clear();
}

int CsvImportData::setColumnAs(int col, csv::ColumnType type)
{
    DATA_TYPE role = type == csv::_intensity_ ? Intensity : Coordinate;

    CsvCoordinateColumn& column = m_selected_cols[role];
    const int prev_assigned = column.columnNumber();
    if (prev_assigned == col && type == column.name())
        return prev_assigned;

    for (auto iter = m_selected_cols.begin(); iter != m_selected_cols.end();)
        if (iter->second.columnNumber() == col && iter->first != role)
            iter = m_selected_cols.erase(iter);
        else
            ++iter;

    column.setColNum(col);
    column.setMultiplier(1.0); // resetting multiplier value
    column.setValues(values(col));
    column.setName(type);
    return prev_assigned;
}

void CsvImportData::setMultiplier(CsvImportData::DATA_TYPE type, double value)
{
    if (m_selected_cols.find(type) == m_selected_cols.end())
        return;

    m_selected_cols[type].setMultiplier(value);
}

void CsvImportData::setFirstRow(size_t row)
{
    if (row >= nRows())
        return;
    m_n_header = row;
}

void CsvImportData::setLastRow(size_t row)
{
    if (row + 1 >= nRows())
        return;
    m_n_footer = nRows() - row - 1;
}

void CsvImportData::toggleDiscardRows(std::set<int> rows)
{
    if (rows.empty()) {
        m_discarded_rows.clear();
        return;
    }
    for (auto row : rows) {
        if (m_discarded_rows.find(row) != m_discarded_rows.end()) {
            m_discarded_rows.erase(row);
        } else {
            m_discarded_rows.insert(row);
        }
    }
}

std::vector<CsvImportData::DATA_TYPE> CsvImportData::availableTypes()
{
    return {Intensity, Coordinate};
}

const csv::DataArray& CsvImportData::data() const
{
    return *m_data.get();
}

int CsvImportData::column(DATA_TYPE type) const
{
    auto iter = m_selected_cols.find(type);
    return iter == m_selected_cols.end() ? -1 : iter->second.columnNumber();
}

csv::DataColumn CsvImportData::values(int col) const
{
    if (col < 0 || col >= static_cast<int>(nCols()))
        return {};

    const size_t size = m_data->size();
    csv::DataColumn result(size);
    for (size_t i = 0; i < size; ++i)
        result[i] = (*m_data)[i][static_cast<size_t>(col)];
    return result;
}

csv::DataColumn CsvImportData::multipliedValues(DATA_TYPE type) const
{
    csv::DataColumn result;
    const int col = column(type);
    if (col < 0 || col >= static_cast<int>(nCols()))
        return result;

    double mult_value = multiplier(type);
    csv::DataColumn col_values = values(col);
    result.resize(col_values.size());
    // FIXME: seems that csv::DataColumn and related
    // classes can be based on QString
    for (size_t i = 0; i < col_values.size(); i++) {
        auto currentText = QString::fromStdString(col_values[i]);
        double number = mult_value * currentText.toDouble();
        // FIXME: find more elegant way to distinguish non-numerics
        QString textToWrite = 0.0 == number ? currentText : QString::number(number);
        result[i] = textToWrite.toStdString();
    }
    return result;
}

double CsvImportData::multiplier(CsvImportData::DATA_TYPE type) const
{
    if (m_selected_cols.find(type) == m_selected_cols.end())
        return 1.0;
    return m_selected_cols.at(type).multiplier();
}

QString CsvImportData::columnLabel(CsvImportData::DATA_TYPE type) const
{
    if (m_selected_cols.find(type) == m_selected_cols.end())
        return QString();
    return csv::HeaderLabels[m_selected_cols.at(type).name()];
}

QList<QString> CsvImportData::availableCoordinateUnits() const
{
    if (column(Coordinate) < 0)
        return {csv::UnitsLabels[AxesUnits::NBINS]};

    auto coordinate_type = m_selected_cols.at(Coordinate).name();
    if (coordinate_type == csv::_q_)
        return {csv::UnitsLabels[AxesUnits::QSPACE]};
    else if (coordinate_type == csv::_theta_)
        return {{csv::UnitsLabels[AxesUnits::DEGREES]}, {csv::UnitsLabels[AxesUnits::RADIANS]}};
    return {csv::UnitsLabels[AxesUnits::NBINS]};
}

size_t CsvImportData::nCols() const
{
    if (nRows() == 0)
        return 0;
    return (*m_data)[0].size();
}

size_t CsvImportData::nRows() const
{
    return (*m_data).size();
}

bool CsvImportData::rowExcluded(int row)
{
    if (static_cast<size_t>(row) < m_n_header || static_cast<size_t>(row) + m_n_footer >= nRows())
        return true;
    if (m_discarded_rows.find(row) != m_discarded_rows.end())
        return true;
    return false;
}

std::set<std::pair<int, int>> CsvImportData::checkData()
{
    std::set<std::pair<int, int>> result;
    for (auto type: availableTypes()) {
        auto col_result = checkFormat(multipliedValues(type), type == Coordinate);
        std::for_each(col_result.begin(), col_result.end(), [col=column(type), &result](int row){
            result.insert({row, col});
        });
    }
    return result;
}

void CsvImportData::resetSelection()
{
    m_n_header = 0;
    m_n_footer = 0;
    m_selected_cols.clear();
    m_discarded_rows.clear();
}

std::set<int> CsvImportData::checkFormat(const csv::DataColumn& values, bool check_ordering)
{
    std::set<int> result;
    if (values.empty())
        return result;

    bool has_prev_value = false;
    double prev_value = 0.0;
    for (size_t i = m_n_header; i + m_n_footer < nRows(); ++i) {
        if (m_discarded_rows.find(static_cast<int>(i)) != m_discarded_rows.end())
            continue;

        auto cellText = QString::fromStdString(values[i]);
        bool is_double;
        double number = cellText.toDouble(&is_double);
        if (!is_double || number <= 0.0) {
            result.insert(static_cast<int>(i));
            continue;
        }

        if (!check_ordering)
            continue;

        if (has_prev_value && prev_value >= number) {
            result.insert(static_cast<int>(i));
            continue;
        }
        prev_value = number;
        has_prev_value = true;
    }
    return result;
}

CsvImportTable::CsvImportTable(QWidget* parent)
    : QTableWidget(parent)
    , m_import_data(new CsvImportData(this))
    , m_data_is_suitable(true)
{}

int CsvImportTable::selectedRow() const
{
    auto selectedRanges = this->selectedRanges();
    if (selectedRanges.empty())
        return -1;
    auto front = selectedRanges.front();
    auto row = front.topRow();
    return row - rowOffset();
}

std::set<int> CsvImportTable::selectedRows() const
{
    std::set<int> accumulator;

    auto selection = selectedRanges();
    if (selection.empty())
        return {};

    int size = selection.size();
    for (int rangenumber = 0; rangenumber < size; ++rangenumber) {
        int row0 = selectedRanges()[rangenumber].topRow() - rowOffset();
        int rowN = selectedRanges()[rangenumber].bottomRow() - rowOffset();
        for (int r = row0; r <= rowN; ++r) {
            accumulator.insert(r);
        }
    }
    return accumulator;
}

int CsvImportTable::selectedColumn() const
{
    auto selectedRanges = this->selectedRanges();
    if (selectedRanges.empty())
        return -1;
    auto front = selectedRanges.front();
    auto col = front.leftColumn();
    return col;
}

void CsvImportTable::setData(csv::DataArray data)
{
    if (data.empty()) {
        clearContents();
        setRowCount(0);
        m_import_data->setData(std::move(data));
        return;
    }

    size_t nRows = data.size();
    size_t nCols = data[0].size();
    clearContents();
    setColumnCount(int(nCols));
    setRowCount(0);

    insertRow(rowCount());

    for (size_t i = 0; i < nRows; i++) {
        insertRow(rowCount());
        size_t I = size_t(rowCount()) - 1;
        for (size_t j = 0; j < data[i].size(); j++) {
            setItem(int(I), int(j), new QTableWidgetItem(QString::fromStdString(data[i][j])));
        }
    }

    m_import_data->setData(std::move(data));
    setMultiplierFields();
}

void CsvImportTable::setColumnAs(int col, csv::ColumnType type)
{
    int prev_col = m_import_data->setColumnAs(col, type);
    resetColumn(prev_col);
    updateSelection();
}

void CsvImportTable::setFirstRow(size_t row)
{
    if (row == m_import_data->firstRow())
        return;
    m_import_data->setFirstRow(row);
    updateSelection();
}

void CsvImportTable::setLastRow(size_t row)
{
    if (row == m_import_data->lastRow())
        return;
    m_import_data->setLastRow(row);
    updateSelection();
}

void CsvImportTable::discardRows(std::set<int> rows)
{
    m_import_data->toggleDiscardRows(std::move(rows));
    updateSelection();
}

void CsvImportTable::resetSelection()
{
    m_import_data->resetSelection();
    updateSelection();
}

double CsvImportTable::intensityMultiplier() const
{
    return m_import_data->multiplier(CsvImportData::Intensity);
}

double CsvImportTable::coordinateMultiplier() const
{
    return m_import_data->multiplier(CsvImportData::Coordinate);
}

QList<QString> CsvImportTable::availableCoordinateUnits() const
{
    return m_import_data->availableCoordinateUnits();
}

void CsvImportTable::updateSelection()
{
    setHeaders();
    // FIXME: replace re-creation of all spin boxes with blocking/unlocking
    setMultiplierFields();
    updateSelectedCols();
    greyoutDiscardedRows();
    if (checkData() != m_data_is_suitable) {
        m_data_is_suitable = !m_data_is_suitable;
        emit dataSanityChanged();
    }
}

// FIXME: put filling vertical headers here
void CsvImportTable::setHeaders()
{
    // Reset header labels
    QStringList headers;

    for (int j = 0; j < this->columnCount(); j++)
        headers.append(QString::number(j + 1));
    setHorizontalHeaderLabels(headers);

    for (auto type: CsvImportData::availableTypes()) {
        int col = m_import_data->column(type);
        if (col < 0)
            continue;
        setHorizontalHeaderItem(col, new QTableWidgetItem(m_import_data->columnLabel(type)));
    }
}

void CsvImportTable::updateSelectedCols()
{
    // FIXME: replace recreation of sell items with value assignment
    for(auto type: CsvImportData::availableTypes()) {
        csv::DataColumn values = m_import_data->multipliedValues(type);
        if (values.empty())
            continue;
        int col = m_import_data->column(type);
        for (size_t i = 0; i < values.size(); ++i)
            setItem(static_cast<int>(i) + rowOffset(), col,
                    new QTableWidgetItem(QString::fromStdString(values[i])));
    }
}

void CsvImportTable::setMultiplierFields()
{
    const int n_cols = static_cast<int>(m_import_data->nCols());

    for (int n = 0; n < n_cols; ++n)
        setCellWidget(0, n, createMultiplierBox());

    auto types = CsvImportData::availableTypes();
    for (auto type : types)
        if (m_import_data->column(type) >= 0) {
            auto spin_box =
                static_cast<ScientificSpinBox*>(cellWidget(0, m_import_data->column(type)));
            spin_box->setEnabled(true);
            spin_box->setValue(m_import_data->multiplier(type));
            connect(spin_box, &ScientificSpinBox::editingFinished, this,
                    [this, spin_box, type]() {
                        m_import_data->setMultiplier(type, spin_box->value());
                        updateSelection();
                    });
        }

    // FIXME: move row headers initialization elsewhere
    int nRows = this->rowCount();

    QStringList vhlabels;
    vhlabels << "Multiplier: ";
    for (int i = rowOffset(); i < nRows; i++)
        vhlabels << QString::number(i);

    this->setVerticalHeaderLabels(vhlabels);
}

void CsvImportTable::greyoutDiscardedRows()
{
    int nRows = this->rowCount();
    int nCols = this->columnCount();

    for (int i = rowOffset(); i < nRows; i++) {
        Qt::GlobalColor color = m_import_data->rowExcluded(i-rowOffset()) ? Qt::gray : Qt::white;
        for (int j = 0; j < nCols; j++)
            markCell(i, j, color);
    }
}

bool CsvImportTable::checkData()
{
    auto to_highlight = m_import_data->checkData();
    for(auto index: to_highlight)
        markCell(index.first + rowOffset(), index.second, Qt::red);
    return to_highlight.empty();
}

void CsvImportTable::resetColumn(int col)
{
    if (columnCount() >= col || col < 0)
        return;

    const csv::DataColumn data = m_import_data->values(col);
    for (size_t i = 0; i < data.size(); i++) {
        QString originalText = QString::fromStdString(data[i]);
        setItem(static_cast<int>(i) + rowOffset(), int(col), new QTableWidgetItem(originalText));
    }
}

void CsvImportTable::markCell(int i, int j, Qt::GlobalColor color)
{
    item(i, j)->setBackground(color);
}
