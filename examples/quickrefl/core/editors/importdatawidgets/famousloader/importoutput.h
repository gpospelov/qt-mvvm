// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTOUTPUT_H
#define IMPORTOUTPUT_H

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace DataImportLogic
{

class DataStructure;
class DataColumn;

// -------------------------------------------------
//! This is the container for one data set
class ParsedFileOutptut
{
public:
    ParsedFileOutptut(const DataStructure& data_structure);
    ~ParsedFileOutptut() = default;

    bool hasAxis() const;
    std::vector<double> axis() const;
    std::string axisName() const;
    std::string axisUnit() const;

    int dataCount() const;
    std::vector<double> data(int column) const;
    std::string dataType(int column) const;
    std::string dataName(int column) const;
    std::string dataUnit(int column) const;

private:
    std::unique_ptr<DataColumn> m_axis_colum;
    std::vector<std::unique_ptr<DataColumn>> m_value_colums;
};

// -------------------------------------------------
//! This is the import structure for multiple files
class ImportOutput
{
public:
    ImportOutput();
    void freezData(const std::string& name, const DataStructure& data_structure);
    std::vector<std::string> keys() const;
    const ParsedFileOutptut* operator[](const std::string& key) const;

    void setTarget(std::string);
    std::string target() const;

private:
    std::map<std::string, std::unique_ptr<ParsedFileOutptut>> m_parsed_outputs;
    std::string m_target;
};

} // namespace DataImportLogic

#endif // IMPORTOUTPUT_H