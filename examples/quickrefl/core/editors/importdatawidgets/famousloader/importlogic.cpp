// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importlogic.h"

#include <sstream>
#include <iostream>
#include <numeric>

//! Standard function to handle spinting
std::vector<std::string> DataImport::split(const std::string &s, char delim) 
{
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

//! Cleans the vector of strings provided by removing empty parts
void DataImport::clean(std::vector<std::string>& input) 
{
    std::vector<std::string>::iterator i = input.begin();
    while(i != input.end())
    {
        if(*i == "")
        {
            i = input.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

//! Transpose the current data array
DataImport::string_data DataImport::transpose(const DataImport::string_data &output)
{
    DataImport::string_data temp_data;
    if (output.size() == 0)
        return temp_data;

    std::vector<size_t> row_size(output.size());
    for (int i = 0; i < output.size(); ++i){
        row_size[i] = output.at(i).size();
    }
    size_t max = *std::max_element(row_size.begin(), row_size.end());

    for (int i = 0; i < *std::max_element(row_size.begin(), row_size.end()); ++i){
        std::vector<std::string> column(output.size(), "");
        for (int j = 0; j <  output.size(); ++j){
            if (i < row_size[j])
                column[j] = output.at(j).at(i);
        }
        temp_data.push_back(column);
    }
    return temp_data;
}

//! Erase All substrings
void DataImport::eraseSubStrings(std::string & main_string, const std::vector<std::string> & string_vector)
{
    std::for_each(string_vector.begin(), string_vector.end(), std::bind(DataImport::eraseAllSubString, std::ref(main_string), std::placeholders::_1));
}

//! Erase All occurences of substring
void DataImport::eraseAllSubString(std::string & main_string, const std::string & to_erase)
{   
    if (to_erase == "")
        return;
        
	// Search for the substring in string in a loop untill nothing is found
    for (std::string::size_type i = main_string.find(to_erase);i != std::string::npos;i = main_string.find(to_erase))
	{
		// If found then erase it from string
		main_string.erase(i, to_erase.length());
	}
}

// -------------------------------------------------
//! This is the constructor of LineFilter
DataImport::LineFilter::LineFilter(std::string name)
    : m_name(name), m_active(false), m_start_line(0), m_end_line(1), m_separator(' '),m_type_string("Data"),m_color("black")
{
}

//! Return only the keys of the separators
std::vector<std::string> DataImport::LineFilter::separatorNames() const
{
    std::vector<std::string> output;
    for(auto const& element : *m_separators) {
        output.push_back(element.first);
    }

    return output;
}

//! Set the right colors in the vector
void DataImport::LineFilter::processColors(std::vector<std::string> &color_vec) const
{
    if (!m_active)
        return ;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (color_vec.size()) : (m_end_line);

    if (start > color_vec.size())
        return ;

    for (int i = start; i < ((end < color_vec.size()) ? (end) : (color_vec.size())); ++i){
        color_vec.at(i) = m_color;
    }
}

//! Set the right separator in the vector
void DataImport::LineFilter::processSeparator(std::vector<char> &separator_vec) const
{
    if (!m_active)
        return ;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (separator_vec.size()) : (m_end_line);

    if (start > separator_vec.size())
        return ;

    for (int i = start; i < ((end < separator_vec.size()) ? (end) : (separator_vec.size())); ++i){
        separator_vec.at(i) = m_separator;
    }
}

//! Set the right type to the vector
void DataImport::LineFilter::processType(std::vector<std::string> &type_vec) const
{
    if (!m_active)
        return ;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (type_vec.size()) : (m_end_line);

    if (start > type_vec.size())
        return ;

    for (int i = start; i < ((end < type_vec.size()) ? (end) : (type_vec.size())); ++i){
        type_vec.at(i) = m_type_string;
    }
}

//! Set the right type to the vector
void DataImport::LineFilter::processIgnore(std::vector<std::vector<std::string>> &ignore_vec) const
{
    if (!m_active)
        return ;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (ignore_vec.size()) : (m_end_line);

    if (start > ignore_vec.size())
        return ;

    for (int i = start; i < ((end < ignore_vec.size()) ? (end) : (ignore_vec.size())); ++i){
        ignore_vec.at(i) = m_ignore_strings;
    }
}

//! Getter for the name
const std::string& DataImport::LineFilter::name() const 
{
    return m_name;
}

//! Getter for the active boolean
const bool& DataImport::LineFilter::active() const
{
    return m_active;
}

//! Getter for the type string
const std::string& DataImport::LineFilter::type() const
{
    return m_type_string;
}

//! Getter for the separator key string
const std::string& DataImport::LineFilter::separator() const
{
    return m_separator_str;
}

//! Getter for the color string
const std::string& DataImport::LineFilter::color() const
{
    return m_color;
}

//! Getter for ignore string
const std::vector<std::string>& DataImport::LineFilter::ignoreStrings() const
{
    return m_ignore_strings;
}

//! Getter for ignore string
std::string DataImport::LineFilter::ignoreString() const
{
    std::string output;
    for (const auto &piece : m_ignore_strings) output += piece;
    return output;
}

//! Getter for the starting line integer
const int& DataImport::LineFilter::start() const
{
    return m_start_line;
}

//! Getter for the ending line integer
const int& DataImport::LineFilter::end() const
{
    return m_end_line;
}

//! Build the separator string
void DataImport::LineFilter::setSeparators(std::map<std::string, char>* separators)
{
    m_separators = separators;
}

//! Set the name
void DataImport::LineFilter::setName(std::string name)
{
    m_name = name;
}

//! Set the active state
void DataImport::LineFilter::setActive(bool active)
{
    m_active = active;
}

//! Set the type
void DataImport::LineFilter::setType(std::string type_string)
{
    m_type_string = type_string;
}

//! Set the separator
void DataImport::LineFilter::setSeparator(std::string separator_name)
{
    m_separator_str = separator_name;
    m_separator = m_separators->at(separator_name);
}

//! Set the color
void DataImport::LineFilter::setColor(std::string color_string)
{
    m_color = color_string;
}

//! Set the ignore strings from a vector of strings
void DataImport::LineFilter::setIgnoreStrings(std::vector<std::string>& ignore_strings)
{
    m_ignore_strings = ignore_strings;
}

//! Set the ignore strings from a single string
void DataImport::LineFilter::setIgnoreString(std::string ignore_string)
{
    std::stringstream ss(ignore_string);
    std::vector<std::string> result;
    while( ss.good() )
    {
        std::string substr;
        getline( ss, substr, ',' );
        result.push_back( substr );
    }
    setIgnoreStrings(result);
}

//! Set the start line
void DataImport::LineFilter::setStart(int start_line)
{
    m_start_line = start_line;
}

//! Set the end line
void DataImport::LineFilter::setEnd(int end_line)
{
    m_end_line = end_line;
}

// -------------------------------------------------
//! This is the constructor
DataImport::ImportLogic::ImportLogic() : QObject()
{
    initSeparators();
    p_data_structure = std::make_unique<DataStructure>();
}

//! This is the slot for adding files into the local memory 
DataImport::LineFilter* DataImport::ImportLogic::addLineFilter(std::string name)
{
    auto temp = std::make_unique<DataImport::LineFilter>(name);
    temp->setSeparators(&m_separators);
    auto address = temp.get();
    m_line_blocks.push_back(std::move(temp));

    return address;
}

//! This is the method removing a particular block given its pointer
void DataImport::ImportLogic::removeLineFilter(DataImport::LineFilter* block_ptr)
{
    m_line_blocks.erase(std::remove_if(m_line_blocks.begin(), m_line_blocks.end(), [=](auto const& ptr){ return ptr.get() == block_ptr; }), m_line_blocks.end());
}

//! This is the slot for adding files into the local memory 
void DataImport::ImportLogic::setFiles(std::vector<std::string> file_paths)
{
    m_files.clear();
    for (auto& file_path : file_paths) {
        auto temp = std::make_unique<CSVFile>(file_path);
        m_files.push_back(std::move(temp));
    }
}

//! build the preview string with html style
std::string DataImport::ImportLogic::getPreview(const int& row) const
{
    auto thumbnail = m_files.at(row)->thumbnail();
    std::vector<std::vector<std::string>> ignore_scheme = getIgnoreScheme(thumbnail.size());
    std::vector<std::string> color_scheme = getColorScheme(thumbnail.size());
    std::vector<char> separator_scheme = getSeparatorScheme(thumbnail.size());

    std::string output;
    for (int i = 0; i < thumbnail.size(); ++i){

        auto formated_line = thumbnail.at(i);
        if (!ignore_scheme.at(i).empty())
            DataImport::eraseSubStrings(formated_line,ignore_scheme.at(i));

        if (separator_scheme.at(i) != '!'){
            auto temp_string_vec = DataImport::split(formated_line, separator_scheme.at(i));
            formated_line = temp_string_vec.at(0);
            for (int j = 1; j < temp_string_vec.size(); ++j){
                formated_line += std::string(std::string("<span style=\"background-color:")+color_scheme.at(i)+std::string("\">")+std::string(1,separator_scheme.at(i))+ std::string("</span>"));
                formated_line += temp_string_vec.at(j);
            }
        }
        output += std::string("<div><font color=\"")+color_scheme.at(i)+std::string("\">") + formated_line+std::string("</font>")+ std::string("</div>");
    }
    return output;
}

//! build the data string vector and return it for given file
DataImport::string_data DataImport::ImportLogic::getData(const int& row) const
{
    auto file_lines = m_files.at(row)->file();
    std::vector<std::vector<std::string>> ignore_scheme = getIgnoreScheme(file_lines.size());
    std::vector<std::string> type_scheme = getTypeScheme(file_lines.size());
    std::vector<char> separator_scheme = getSeparatorScheme(file_lines.size());

    DataImport::string_data output;
    for (int i = 0; i < file_lines.size(); ++i){
        if (type_scheme.at(i) != "Data")
            continue;

        auto line = file_lines.at(i);
        if (!ignore_scheme.at(i).empty())
            DataImport::eraseSubStrings(line,ignore_scheme.at(i));

        auto temp_string_vec = DataImport::split(line, separator_scheme.at(i));
        DataImport::clean(temp_string_vec);
        output.push_back(temp_string_vec);
    }
    return output;
}

//! Build the map of headers in the file with their associated column
DataImport::header_map DataImport::ImportLogic::getHeader(const int& row) const
{
    auto file_lines = m_files.at(row)->file();
    std::vector<std::vector<std::string>> ignore_scheme = getIgnoreScheme(file_lines.size());
    std::vector<std::string> type_scheme = getTypeScheme(file_lines.size());
    std::vector<char> separator_scheme = getSeparatorScheme(file_lines.size());

    DataImport::header_map output;
    for (int i = 0; i < file_lines.size(); ++i){
        if (type_scheme.at(i) == "Header"){

            auto line = file_lines.at(i);
            if (!ignore_scheme.at(i).empty())
                DataImport::eraseSubStrings(line,ignore_scheme.at(i));

            auto temp_string_vec = DataImport::split(line, separator_scheme.at(i));
            DataImport::clean(temp_string_vec);
            for (int j = 0; j< temp_string_vec.size(); ++j){
                output.insert(std::make_pair(temp_string_vec.at(j),j));
            }
            break;
        }
    }
    return output;
}

//! Grab the data and header internally and then populate the data structure
void DataImport::ImportLogic::updateData(const int& row)
{
    auto headers = getHeader(row);
    auto data = DataImport::transpose(getData(row));

    if (!headers.empty())
        p_data_structure->setData(headers, data);
    else
        p_data_structure->setData(data);
}

//! Grab the data and header internally and then populate the data structure
DataImport::DataStructure* DataImport::ImportLogic::dataStructure() const
{
    return p_data_structure.get();
}

//! Get the names of all the LineFilters in place
DataImport::LineFilter* DataImport::ImportLogic::nameInBlocks(const std::string &name) const
{
    for (auto &line_block: m_line_blocks){
        if (name == line_block->name()) return line_block.get();
    }
    return nullptr;
}

//! Get the names of all the LineFilters in place
DataImport::LineFilter* DataImport::ImportLogic::typeInBlocks(const std::string &type) const
{
    for (auto &line_block: m_line_blocks){
        if (type == line_block->type()) return line_block.get();
    }
    return nullptr;
}

//! build the preview string with html style
void DataImport::ImportLogic::initSeparators()
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
std::vector<std::string> DataImport::ImportLogic::getColorScheme(const int& length) const
{
    std::vector<std::string> output(length, "black");
    for (auto &line_block : m_line_blocks){
        line_block->processColors(output);
    }
    return output;
}

//! Get the separator scheme
std::vector<char> DataImport::ImportLogic::getSeparatorScheme(const int& length) const
{
    std::vector<char> output(length, '!');
    for (auto &line_block : m_line_blocks){
        line_block->processSeparator(output);
    }
    return output;
}

//! Get the type scheme
std::vector<std::string> DataImport::ImportLogic::getTypeScheme(const int& length) const
{
    std::vector<std::string> output(length, "Comments");
    for (auto &line_block : m_line_blocks){
        line_block->processType(output);
    }
    return output;
}

//! Get the type scheme
std::vector<std::vector<std::string>> DataImport::ImportLogic::getIgnoreScheme(const int& length) const
{
    std::vector<std::vector<std::string>> output(length, std::vector<std::string>());
    for (auto &line_block : m_line_blocks){
        line_block->processIgnore(output);
    }
    return output;
}
