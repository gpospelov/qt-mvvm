// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportTable.h
//! @brief     Defines class CsvImportTable
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IMPORTTABLEVIEW_H
#define IMPORTTABLEVIEW_H

#include <QTableWidget>
#include <memory>
#include <set>

namespace csv
{
enum ColumnType { _intensity_, _theta_, _q_ };
const QStringList HeaderLabels{"Intensity", "theta", "q"};
const QStringList UnitsLabels{"default", "bin", "rad", "deg", "mm", "1/nm"};
typedef std::vector<std::vector<std::string>> DataArray;
typedef std::vector<std::string> DataRow;
typedef std::vector<std::string> DataColumn;
} // namespace csv

namespace DataImport
{

// Convention
using string_data = std::vector<std::vector<std::string>>;

struct AxesUnitsWrap {
    enum AxesUnits { DEFAULT, NBINS, RADIANS, DEGREES, MM, QSPACE, QXQY, RQ4 };
};
typedef AxesUnitsWrap::AxesUnits AxesUnits;

class CsvIntensityColumn
{
public:
    // Constructors:
    CsvIntensityColumn();
    CsvIntensityColumn(const CsvIntensityColumn& toCopy);
    CsvIntensityColumn(int colNum, double multiplier, csv::DataColumn values);

    // Getters:
    int columnNumber() const;
    double multiplier() const;
    csv::DataColumn values() const;

    // Setters:
    void setColNum(int const colNum);
    void setMultiplier(double const multiplier);
    void setValues(csv::DataColumn const values);
    void resetColumn(int colNum = -1, double multiplier = 1., csv::DataColumn values = {});

private:
    int m_colNum;
    double m_multiplier;
    csv::DataColumn m_values;
};

class CsvCoordinateColumn : public CsvIntensityColumn
{
public:
    // Constructors:
    CsvCoordinateColumn();
    CsvCoordinateColumn(const CsvCoordinateColumn& toCopy);
    CsvCoordinateColumn(int colNum, double multiplier, csv::DataColumn values, AxesUnits units);

    // Getters:
    AxesUnits units() const;
    csv::ColumnType name() const { return m_name; }

    // Setters:
    void setUnits(AxesUnits const units);
    void setName(csv::ColumnType const name);
    void resetColumn(int colNum = -1, double multiplier = 1., csv::DataColumn values = {},
                     AxesUnits units = AxesUnits::NBINS, csv::ColumnType name = csv::_intensity_);

private:
    AxesUnits m_units;
    csv::ColumnType m_name;
};

class CsvImportData : public QObject
{
public:
    // FIXME: move DATA_TYPE enumeration to csv namespace
    enum DATA_TYPE { Intensity, Coordinate };

    CsvImportData(QObject* parent = nullptr);

    void setData(csv::DataArray data);
    //! sets _type_ to a column _col_. Returns the
    //! column number previously set to the type
    int setColumnAs(int col, csv::ColumnType type);
    void setMultiplier(DATA_TYPE type, double value);
    void setFirstRow(size_t row);
    void setLastRow(size_t row);
    void toggleDiscardRows(std::set<int> rows);

    // static methods
    // FIXME: move to csv namespace or utilities
    static std::vector<DATA_TYPE> availableTypes();
    // accessors
    const csv::DataArray& data() const;
    int column(DATA_TYPE type) const;
    csv::DataColumn values(int col) const;
    csv::DataColumn multipliedValues(DATA_TYPE type) const;
    double multiplier(DATA_TYPE type) const;
    QString columnLabel(DATA_TYPE type) const;
    QList<QString> availableCoordinateUnits() const;
    std::set<int> rowsToDiscard() const { return m_discarded_rows; }
    size_t nCols() const;
    size_t nRows() const;
    bool rowExcluded(int row);
    size_t firstRow() { return m_n_header; }
    size_t lastRow() { return m_n_footer + 1 >= nRows() ? 0 : nRows() - m_n_footer - 1; }

    std::set<std::pair<int, int>> checkData();
    void resetSelection();

private:
    //! Checks if selected data is suitable for import.
    //! All values must be convertible to doubles, positive and
    //! sorted in ascending order if _check_ordering_ is set to true.
    //! Returns a set of rows where the check failed.
    std::set<int> checkFormat(const csv::DataColumn& values, bool check_ordering);

    std::unique_ptr<const csv::DataArray> m_data;
    std::map<DATA_TYPE, CsvCoordinateColumn> m_selected_cols;
    size_t m_n_header; //!< number of header rows
    size_t m_n_footer; //!< number of footer rows
    std::set<int> m_discarded_rows;
};

class ImportTableView : public QTableWidget
{
    Q_OBJECT
public:
    ImportTableView(QWidget* parent = nullptr);

    int selectedRow() const;
    std::set<int> selectedRows() const;
    int selectedColumn() const;

    void setData(const string_data& data);
    void setColumnAs(int col, csv::ColumnType type);
    void setFirstRow(size_t row);
    void setLastRow(size_t row);
    void discardRows(std::set<int> rows);
    void resetSelection();

    // accessors
    int intensityColumn() const { return m_import_data->column(CsvImportData::Intensity); }
    int coordinateColumn() const { return m_import_data->column(CsvImportData::Coordinate); }
    double intensityMultiplier() const;
    double coordinateMultiplier() const;
    QList<QString> availableCoordinateUnits() const;
    std::set<int> rowsToDiscard() const { return m_import_data->rowsToDiscard(); }
    bool dataLooksGood() const { return m_data_is_suitable; }

signals:
    void dataSanityChanged();

private:
    void updateSelection();
    void setHeaders();
    void updateSelectedCols(); // replacement for applyMultipliers
    void setMultiplierFields();
    void greyoutDiscardedRows();
    bool checkData();
    void resetColumn(int col);
    int rowOffset() const { return 1; } // this comes from the multipliers in the first row

    void markCell(int i, int j, Qt::GlobalColor color);

    CsvImportData* m_import_data;
    bool m_data_is_suitable;
};

}

#endif // IMPORTTABLEVIEW_H
