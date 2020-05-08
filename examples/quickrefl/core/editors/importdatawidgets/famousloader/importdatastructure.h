// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTDATASTRUCTURE_H
#define IMPORTDATASTRUCTURE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace DataImportLogic
{

// Convention
using string_data = std::vector<std::vector<std::string>>;
using header_map = std::map<std::string, int>;

// global constants
enum InfoTypes { Name, Type, Unit, Multiplier, Header };
const std::vector<std::string> InfoNames{"Name", "Type", "Unit", "Multiplier", "Header"};
const std::vector<std::string> Types{"Intensity", "Axis"};
const std::vector<std::string> Units{"a.u.", "counts", "bin", "rad", "deg", "mm", "1/nm"};

// -------------------------------------------------
//! This is the column object for the data
class DataColumn
{
public:
    DataColumn();
    DataColumn(const std::string& header);
    ~DataColumn() = default;

    void setValues(std::vector<std::string>& values);
    void setValues(std::vector<double>& values);
    void clearValues();
    int rowCount();

    void setName(std::string& name);
    void setType(std::string& type);
    void setHeader(std::string& header);
    void setUnit(std::string& unit);
    void setColNum(int column_num);
    void setMultiplier(double multiplier);

    const std::vector<double>& values() const;
    std::vector<double> finalValues() const;
    double value(int row) const;
    double finalValue(int row) const;
    const std::string& name() const;
    const std::string& type() const;
    const std::string& header() const;
    const std::string& unit() const;
    int colNum() const;
    double multiplier() const;

private:
    std::string m_name;
    std::string m_type;
    std::string m_header;
    std::string m_unit;
    double m_multiplier;
    int m_column_num;
    std::vector<double> m_values;
};

// -------------------------------------------------
//! This will manage all the column objects
class DataStructure
{
public:
    DataStructure();
    ~DataStructure() = default;

    void setData(int row, int column);
    void setData(string_data& data);
    void setData(header_map& headers, string_data& data);

    void processHeaders(int num);
    void processHeaders(const std::vector<std::string>& headers);
    std::vector<bool> checkHeaders(const std::vector<std::string>& headers);

    DataColumn* column(const std::string& header);
    DataColumn* column(int column);

    int rowCount() const;
    int columnCount() const;

private:
    void addColumn(const std::string& header);
    void delColumn(const std::string& header);
    void clearColumnValues();

private:
    std::vector<std::unique_ptr<DataColumn>> m_data_columns;
};

} // end of namespace DataImportLogic

#endif // IMPORTDATASTRUCTURE_H
