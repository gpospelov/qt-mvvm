// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importdatastructure.h"

#include <algorithm>
#include <cmath>

namespace DataImportLogic
{

// -------------------------------------------------
//! This is the constructor of DataColumn
DataColumn::DataColumn()
    : m_name("No Name"), m_type("Intensity"), m_header(""), m_unit("a.u."), m_multiplier(1.),
      m_column_num(0)
{
}

DataColumn::DataColumn(const std::string& header)
    : m_name("No Name"), m_type("Intensity"), m_header(header), m_unit("a.u."), m_multiplier(1.),
      m_column_num(0)
{
}

//! Setter for the values (str)
void DataColumn::setValues(std::vector<std::string>& values)
{
    clearValues();
    for (const auto& value : values) {
        double value_double;
        try {
            value_double = std::stod(value);
        } catch (std::exception& e) {
            value_double = std::nan("");
        }
        m_values.push_back(value_double);
    }
}

//! Setter for the values (doubles)
void DataColumn::setValues(std::vector<double>& values)
{
    m_values = values;
}

//! Clear the values int the column
void DataColumn::clearValues()
{
    m_values.clear();
}

//! Retrieve the current row count
int DataColumn::rowCount()
{
    return m_values.size();
}

//! Setter for the name
void DataColumn::setName(std::string& name)
{
    m_name = name;
}

//! Setter for the type
void DataColumn::setType(std::string& type)
{
    m_type = type;
}

//! Setter for the header
void DataColumn::setHeader(std::string& header)
{
    m_header = header;
}

//! Setter for the units
void DataColumn::setUnit(std::string& unit)
{
    m_unit = unit;
}

//! Setter for the columns
void DataColumn::setColNum(int column_num)
{
    m_column_num = column_num;
}

//! Setter for the multiplier
void DataColumn::setMultiplier(double multiplier)
{
    m_multiplier = multiplier;
}

//! Getter for the data values
const std::vector<double>& DataColumn::values() const
{
    return m_values;
}

//! Getter for the data value at row
double DataColumn::value(int row) const
{
    return m_values.at(row);
}

//! Getter for the data value at row
double DataColumn::finalValue(int row) const
{
    return m_values.at(row) * multiplier();
}

//! Getter for the name
const std::string& DataColumn::name() const
{
    return m_name;
}

//! Getter for the type
const std::string& DataColumn::type() const
{
    return m_type;
}

//! Getter for the header
const std::string& DataColumn::header() const
{
    return m_header;
}

//! Getter for the unit
const std::string& DataColumn::unit() const
{
    return m_unit;
}

//! Getter for the column number
int DataColumn::colNum() const
{
    return m_column_num;
}

//! Getter for the multiplier
double DataColumn::multiplier() const
{
    return m_multiplier;
}

// -------------------------------------------------
//! This is the constructor of DataStructure
DataStructure::DataStructure() {}

//! This is the set data routine used if not header data is provided
void DataStructure::setData(string_data& data)
{
    clearColumnValues();
    processHeaders(data.size());

    for (int i = 0; i < data.size(); ++i) {
        m_data_columns.at(i)->setValues(data.at(i));
    }
}

//! This is the set data routine used if header data is provided
void DataStructure::setData(header_map& headers, string_data& data)
{
    std::vector<std::string> keys;
    for (header_map::iterator it = headers.begin(); it != headers.end(); ++it) {
        keys.push_back(it->first);
    }

    clearColumnValues();
    processHeaders(keys);

    for (const auto& header : keys) {
        DataColumn* data_column = column(header);
        if (headers[header] < data.size())
            data_column->setValues(data.at(headers[header]));
    }
}

//! Process the headers (add columns if missmatch)
void DataStructure::processHeaders(int num)
{
    for (int i = m_data_columns.size(); i < num; ++i) {
        addColumn("");
    }
}

//! Process the headers (add columns if missmatch)
void DataStructure::processHeaders(const std::vector<std::string>& headers)
{
    for (const auto& header : headers) {
        if (column(header) == nullptr) {
            addColumn(header);
        }
    }
}

//! Check which header is present or not
std::vector<bool> DataStructure::checkHeaders(const std::vector<std::string>& headers)
{
    std::vector<bool> output;
    for (const auto& header : headers) {
        output.push_back((column(header) == nullptr) ? (false) : (true));
    }
    return output;
}

//! Check that the headers coincide
DataColumn* DataStructure::column(const std::string& header)
{
    auto found = std::find_if(
        m_data_columns.begin(), m_data_columns.end(),
        [header](const std::unique_ptr<DataColumn>& column) { return column->header() == header; });
    return (found == m_data_columns.end()) ? (nullptr) : ((*found).get());
}

//! Get the column associated to an index
DataColumn* DataStructure::column(int column_num)
{
    int column_idx = 0;
    for (const auto& column : m_data_columns) {
        if (column->rowCount() != 0) {
            if (column_idx == column_num) {
                return column.get();
            } else {
                ++column_idx;
            }
        }
    }
    return nullptr;
}

//! Add a DataColumn item
void DataStructure::addColumn(const std::string& header)
{
    auto new_column = std::make_unique<DataColumn>(header);
    m_data_columns.push_back(std::move(new_column));
}

//! Check that the headers coincide TODO
void DataStructure::delColumn(const std::string& header) {}

//! Clear the data content of the columns
void DataStructure::clearColumnValues()
{
    if (m_data_columns.empty())
        return;

    for (auto& column : m_data_columns) {
        column->clearValues();
    }
}

//! Retrieve the row count
int DataStructure::rowCount() const
{
    int row_count = 0;
    for (const auto& data_column : m_data_columns) {
        if (data_column->rowCount() > row_count)
            row_count = data_column->rowCount();
    }
    return row_count;
}

//! retrieve the column count
int DataStructure::columnCount() const
{
    int column_size = 0;
    for (const auto& column : m_data_columns) {
        if (column->rowCount() != 0)
            ++column_size;
    }
    return column_size;
}

} // end of namespace DataImportLogic
