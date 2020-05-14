// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importlogic.h"
#include "importdatacolumn.h"

namespace DataImportLogic
{
//! This is the constructor
ImportLogic::ImportLogic()
{
    initSeparators();
    p_data_structure = std::make_unique<DataStructure>();
}

//! This is the slot for adding files into the local memory
LineFilter* ImportLogic::addLineFilter(std::string name)
{
    auto temp = std::make_unique<LineFilter>(name);
    temp->setSeparators(&m_separators);
    auto address = temp.get();
    m_line_filters.push_back(std::move(temp));

    return address;
}

//! This is the method removing a particular block given its pointer
void ImportLogic::removeLineFilter(LineFilter* block_ptr)
{
    m_line_filters.erase(std::remove_if(m_line_filters.begin(), m_line_filters.end(),
                                        [=](auto const& ptr) { return ptr.get() == block_ptr; }),
                         m_line_filters.end());
}

//! This is the method reordering line filter
void ImportLogic::setLineFilterOrder(std::vector<LineFilter*> filter_order)
{
    std::vector<std::unique_ptr<LineFilter>> temp;
    for (LineFilter* line_filter_ptr : filter_order) {
        const auto found_ptr =
            std::find_if(m_line_filters.begin(), m_line_filters.end(),
                         [=](auto const& ptr) { return ptr.get() == line_filter_ptr; });
        temp.push_back(std::move(*found_ptr));
        m_line_filters.erase(found_ptr);
    }
    std::move(temp.begin(), temp.end(), std::back_inserter(m_line_filters));
}

//! This is the slot for adding files into the local memory
void ImportLogic::setFiles(const std::vector<std::string>& file_paths)
{
    m_files.clear();
    for (auto& file_path : file_paths) {
        auto temp = std::make_unique<CSVFile>(file_path);
        m_files.push_back(std::move(temp));
    }
}

//! Process all files and then send the output
ImportOutput ImportLogic::getFinalOutput()
{
    ImportOutput output;
    for (int i = 0; i < m_files.size(); ++i) {
        updateData(i);
        output.freezData(m_files.at(i)->path(), *(p_data_structure.get()));
    }
    return output;
}

//! build the preview string with html style
std::string ImportLogic::getPreview(const int& row) const
{
    auto thumbnail = m_files.at(row)->thumbnail();
    std::vector<std::vector<std::string>> ignore_scheme = getIgnoreScheme(thumbnail.size());
    std::vector<std::string> color_scheme = getColorScheme(thumbnail.size());
    std::vector<char> separator_scheme = getSeparatorScheme(thumbnail.size());

    std::string output = "";
    for (int i = 0; i < thumbnail.size(); ++i) {

        auto formated_line = thumbnail.at(i);
        if (!ignore_scheme.at(i).empty())
            DataImportUtils::eraseSubStrings(formated_line, ignore_scheme.at(i));

        if (separator_scheme.at(i) != '!') {
            auto temp_string_vec = DataImportUtils::split(formated_line, separator_scheme.at(i));
            if (temp_string_vec.size() != 0) {
                formated_line = temp_string_vec.at(0);
                for (int j = 1; j < temp_string_vec.size(); ++j) {
                    formated_line += std::string(std::string("<span style=\"background-color:")
                                                 + color_scheme.at(i) + std::string("\">")
                                                 + std::string(1, separator_scheme.at(i))
                                                 + std::string("</span>"));
                    formated_line += temp_string_vec.at(j);
                }
            }
        }
        output += std::string("<div><font color=\"") + color_scheme.at(i) + std::string("\">")
                  + formated_line + std::string("</font>") + std::string("</div>");
    }
    return output;
}

//! build the data string vector and return it for given file
DataImportUtils::string_data ImportLogic::getData(const int& row) const
{
    auto file_lines = m_files.at(row)->file();
    std::vector<std::vector<std::string>> ignore_scheme = getIgnoreScheme(file_lines.size());
    std::vector<std::string> type_scheme = getTypeScheme(file_lines.size());
    std::vector<char> separator_scheme = getSeparatorScheme(file_lines.size());

    DataImportUtils::string_data output;
    for (int i = 0; i < file_lines.size(); ++i) {
        if (type_scheme.at(i) != "Data")
            continue;

        auto line = file_lines.at(i);
        if (!ignore_scheme.at(i).empty())
            DataImportUtils::eraseSubStrings(line, ignore_scheme.at(i));

        auto temp_string_vec = DataImportUtils::split(line, separator_scheme.at(i));
        DataImportUtils::clean(temp_string_vec);
        output.push_back(temp_string_vec);
    }
    return output;
}

//! Build the map of headers in the file with their associated column
DataImportUtils::header_map ImportLogic::getHeader(const int& row) const
{
    auto file_lines = m_files.at(row)->file();
    std::vector<std::vector<std::string>> ignore_scheme = getIgnoreScheme(file_lines.size());
    std::vector<std::string> type_scheme = getTypeScheme(file_lines.size());
    std::vector<char> separator_scheme = getSeparatorScheme(file_lines.size());

    DataImportUtils::header_map output;
    for (int i = 0; i < file_lines.size(); ++i) {
        if (type_scheme.at(i) == "Header") {

            auto line = file_lines.at(i);
            if (!ignore_scheme.at(i).empty())
                DataImportUtils::eraseSubStrings(line, ignore_scheme.at(i));

            auto temp_string_vec = DataImportUtils::split(line, separator_scheme.at(i));
            DataImportUtils::clean(temp_string_vec);
            for (int j = 0; j < temp_string_vec.size(); ++j) {
                output.insert(std::make_pair(temp_string_vec.at(j), j));
            }
            break;
        }
    }
    return output;
}

//! Grab the data and header internally and then populate the data structure
void ImportLogic::updateData(const int& row)
{
    auto headers = getHeader(row);
    auto data = DataImportUtils::transpose(getData(row));

    if (!headers.empty())
        p_data_structure->setData(headers, data);
    else
        p_data_structure->setData(data);
}

//! Grab the data and header internally and then populate the data structure
DataStructure* ImportLogic::dataStructure() const
{
    return p_data_structure.get();
}

//! Get the names of all the LineFilters in place
LineFilter* ImportLogic::nameInFilters(const std::string& name) const
{
    for (auto& line_filter : m_line_filters) {
        if (name == line_filter->name())
            return line_filter.get();
    }
    return nullptr;
}

//! Get the names of all the LineFilters in place
LineFilter* ImportLogic::typeInFilters(const std::string& type) const
{
    for (auto& line_filter : m_line_filters) {
        if (type == line_filter->type())
            return line_filter.get();
    }
    return nullptr;
}

//! build the preview string with html style
void ImportLogic::initSeparators()
{
    m_separators.insert(std::pair<std::string, char>("Space ( )", ' '));
    m_separators.insert(std::pair<std::string, char>("Comma (,)", ','));
    m_separators.insert(std::pair<std::string, char>("Semicolon (;)", ';'));
    m_separators.insert(std::pair<std::string, char>("Pipe (|)", '|'));
    m_separators.insert(std::pair<std::string, char>("Colon (:)", ':'));
    m_separators.insert(std::pair<std::string, char>("Tab", '\t'));
    m_separators.insert(std::pair<std::string, char>("Quote (\')", '\''));
    m_separators.insert(std::pair<std::string, char>("Apostrophe (\")", '\"'));
}

//! Get the color scheme
std::vector<std::string> ImportLogic::getColorScheme(const int& length) const
{
    std::vector<std::string> output(length, "black");
    for (auto& line_filter : m_line_filters) {
        line_filter->processColors(output);
    }
    return output;
}

//! Get the separator scheme
std::vector<char> ImportLogic::getSeparatorScheme(const int& length) const
{
    std::vector<char> output(length, '!');
    for (auto& line_filter : m_line_filters) {
        line_filter->processSeparator(output);
    }
    return output;
}

//! Get the type scheme
std::vector<std::string> ImportLogic::getTypeScheme(const int& length) const
{
    std::vector<std::string> output(length, "Comments");
    for (auto& line_filter : m_line_filters) {
        line_filter->processType(output);
    }
    return output;
}

//! Get the type scheme
std::vector<std::vector<std::string>> ImportLogic::getIgnoreScheme(const int& length) const
{
    std::vector<std::vector<std::string>> output(length, std::vector<std::string>());
    for (auto& line_filter : m_line_filters) {
        line_filter->processIgnore(output);
    }
    return output;
}

} // namespace DataImportLogic
