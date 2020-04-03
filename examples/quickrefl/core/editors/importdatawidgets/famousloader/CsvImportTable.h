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

#ifndef CSVIMPORTTABLE_H
#define CSVIMPORTTABLE_H

#include "CsvDataColumn.h"
#include "CsvNamespace.h"
#include <QTableWidget>
#include <set>

class BA_CORE_API_ CsvImportData : public QObject
{
public:
    // FIXME: move DATA_TYPE enumeration to csv namespace
    enum DATA_TYPE {Intensity, Coordinate };

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
    std::set<int> rowsToDiscard() const {return m_discarded_rows;}
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

class CsvImportTable : public QTableWidget
{
    Q_OBJECT
public:
    CsvImportTable(QWidget* parent = nullptr);

    int selectedRow() const;
    std::set<int> selectedRows() const;
    int selectedColumn() const;

    void setData(csv::DataArray data);
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

#endif // CSVIMPORTTABLE_H
