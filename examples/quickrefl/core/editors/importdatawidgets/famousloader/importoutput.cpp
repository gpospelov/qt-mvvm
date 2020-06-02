// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/ImportTableView.cpp
//! @brief     Implements class ImportTableView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "importoutput.h"
#include "importdatastructure.h"
#include "importdatacolumn.h"

namespace DataImportLogic
{

// -------------------------------------------------
//! This is the container for one data set

//! This is the constructor
ParsedFileOutptut::ParsedFileOutptut(const DataStructure& data_structure) : m_axis_colum()
{
    for (int i = 0; i < data_structure.columnCount(); ++i) {
        auto column = data_structure.column(i);

        // Ignore the columns marked as such
        if (column->type() == "Ignore")
            continue;

        if (column->type() == "Axis") {
            m_axis_colum = std::make_unique<DataColumn>(*column);
        } else {
            m_value_colums.push_back(std::make_unique<DataColumn>(*column));
        }
    }
}

//! This will return true if an axis item exists
bool ParsedFileOutptut::hasAxis() const
{
    return (m_axis_colum) ? (true) : (false);
}

//! This will return the final values of the axis column
std::vector<double> ParsedFileOutptut::axis() const
{
    return (hasAxis()) ? (m_axis_colum->finalValues()) : (std::vector<double>());
}

//! This will return th ename of the axis if present
std::string ParsedFileOutptut::axisName() const
{
    return (hasAxis()) ? (m_axis_colum->name()) : ("");
}

//! This will return the unit of the axis if present
std::string ParsedFileOutptut::axisUnit() const
{
    return (hasAxis()) ? (m_axis_colum->unit()) : ("a.u.");
}

//! This will return the count of the data vector
int ParsedFileOutptut::dataCount() const
{
    return m_value_colums.size();
}

//! This will return the data of the asked column
std::vector<double> ParsedFileOutptut::data(int column) const
{
    return m_value_colums.at(column)->finalValues();
}

//! This will return the type of the said column
std::string ParsedFileOutptut::dataType(int column) const
{
    return m_value_colums.at(column)->type();
}

//! This will return th ename of the said column
std::string ParsedFileOutptut::dataName(int column) const
{
    return m_value_colums.at(column)->name();
}

//! This will return the unit of the said column
std::string ParsedFileOutptut::dataUnit(int column) const
{
    return m_value_colums.at(column)->unit();
}

// -------------------------------------------------
//! This is the import structure for multiple files
ImportOutput::ImportOutput() {}

//! Freez the data
void ImportOutput::freezData(const std::string& name, const DataStructure& data_structure)
{
    auto parsed_file_output = std::make_unique<ParsedFileOutptut>(data_structure);
    m_parsed_outputs.insert(std::make_pair(name, std::move(parsed_file_output)));
}

//! Get the keys of the map
std::vector<std::string> ImportOutput::keys() const
{
    std::vector<std::string> keys;
    for (auto it = m_parsed_outputs.begin(); it != m_parsed_outputs.end(); ++it) {
        keys.push_back(it->first);
    }
    return keys;
}

//! Define the retrieval operator
const ParsedFileOutptut* ImportOutput::operator[](const std::string& key) const
{
    return m_parsed_outputs.at(key).get();
}

void ImportOutput::setMerge(bool merge)
{
    m_merge = merge;
}

bool ImportOutput::merge() const
{
    return m_merge;
}

} // namespace DataImportLogic
