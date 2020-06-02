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
#include <functional>

namespace DataImportLogic
{
//! This is the constructor of DataStructure
DataStructure::DataStructure() {}

//! This is the set data routine used if not header data is provided
void DataStructure::setData(DataImportUtils::string_data& data)
{
    clearColumnValues();
    processHeaders(data.size());

    for (int i = 0; i < data.size(); ++i) {
        m_data_columns.at(i)->setValues(data.at(i));
    }
}

//! This is the set data routine used if header data is provided
void DataStructure::setData(DataImportUtils::header_map& headers, DataImportUtils::string_data& data)
{
    std::vector<std::string> keys;
    for (DataImportUtils::header_map::iterator it = headers.begin(); it != headers.end(); ++it) {
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

//! Get the column associated to an index (! This is the const implementation)
const DataColumn* DataStructure::column(int column_num) const
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
    std::unique_ptr<DataColumn> new_column;
    if (m_data_columns.empty()) {
        new_column = std::make_unique<DataColumn>(header);
        std::string type("Axis");
        new_column->setType(type);
    } else {
        new_column = std::make_unique<DataColumn>(header);
    }

    if (m_history.size()>m_data_columns.size()+1){
        new_column->setName(m_history.at(m_data_columns.size()).at(0));
        new_column->setType(m_history.at(m_data_columns.size()).at(1));
        new_column->setUnit(m_history.at(m_data_columns.size()).at(2));
        new_column->setMultiplier(std::stod(m_history.at(m_data_columns.size()).at(3)));
    }

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

//! This will set the column history to remember loading
void DataStructure::setColumnHistory(DataImportUtils::string_data history)
{
    m_history = history;
}

//! This provide the column history meant to be stored in QSettings
DataImportUtils::string_data DataStructure::columnHistory() const
{
    DataImportUtils::string_data history;

    for (int i = 0; i < columnCount(); ++i){
        history.push_back(std::vector<std::string> {
            column(i)->name(),
            column(i)->type(),
            column(i)->unit(),
            std::to_string(column(i)->multiplier())
        });
    }

    return history;
}

} // end of namespace DataImportLogic
