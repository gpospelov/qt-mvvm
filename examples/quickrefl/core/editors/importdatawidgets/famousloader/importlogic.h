// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTLOGIC_H
#define IMPORTLOGIC_H

#include "importfile.h"
#include "importlinefilter.h"
#include "importdatastructure.h"
#include "importoutput.h"
#include "importutils.h"

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace DataImportLogic
{

//! Here sits all the logic for the importation of data
class ImportLogic
{
public:
    ImportLogic();
    ~ImportLogic() = default;

    LineFilter* addLineFilter(std::string name);
    void removeLineFilter(LineFilter* block_ptr);
    void setLineFilterOrder(std::vector<LineFilter*> filter_order);

    std::string getPreview(const int& row) const;
    DataImportUtils::string_data getData(const int& row) const;
    DataImportUtils::header_map getHeader(const int& row) const;
    void updateData(const int& row);
    DataStructure* dataStructure() const;

    LineFilter* nameInFilters(const std::string& name) const;
    LineFilter* typeInFilters(const std::string& type) const;
    void setFiles(const std::vector<std::string>& file_paths);

    ImportOutput getFinalOutput();

private:
    void initSeparators();
    std::vector<std::string> getColorScheme(const int& length) const;
    std::vector<char> getSeparatorScheme(const int& length) const;
    std::vector<std::string> getTypeScheme(const int& length) const;
    std::vector<std::vector<std::string>> getIgnoreScheme(const int& length) const;

private:
    std::vector<std::unique_ptr<ImportFile>> m_files;
    std::vector<std::unique_ptr<LineFilter>> m_line_filters;
    std::map<std::string, char> m_separators;
    std::unique_ptr<DataStructure> p_data_structure;
};

} // namespace DataImportLogic

#endif // IMPORTLOGIC_H