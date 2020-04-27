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

//! Standat function to handle spinting
std::vector<std::string> DataImport::split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

// -------------------------------------------------
//! This is the constructor of LineBlock
DataImport::LineBlock::LineBlock(std::string name)
    : m_name(name), m_active(false), m_start_line(0), m_end_line(1), m_separator(' '),m_type_string("Data"),m_color("black")
{
}

//! Return only the keys of the separators
std::vector<std::string> DataImport::LineBlock::separatorNames() const
{
    std::vector<std::string> output;
    for(auto const& element : *m_separators) {
        output.push_back(element.first);
    }

    return output;
}

//! Set the right colors in the vector
void DataImport::LineBlock::processColors(std::vector<std::string> &color_vec) const
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
void DataImport::LineBlock::processSeparator(std::vector<char> &separator_vec) const
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

//! Getter for the name
const std::string& DataImport::LineBlock::name() const 
{
    return m_name;
}

//! Getter for the active boolean
const bool& DataImport::LineBlock::active() const
{
    return m_active;
}

//! Getter for the type string
const std::string& DataImport::LineBlock::type() const
{
    return m_type_string;
}

//! Getter for the separator key string
const std::string& DataImport::LineBlock::separator() const
{
    return m_separator_str;
}

//! Getter for the color string
const std::string& DataImport::LineBlock::color() const
{
    return m_color;
}

//! Getter for the starting line integer
const int& DataImport::LineBlock::start() const
{
    return m_start_line;
}

//! Getter for the ending line integer
const int& DataImport::LineBlock::end() const
{
    return m_end_line;
}

//! Build the separator string
void DataImport::LineBlock::setSeparators(std::map<std::string, char>* separators)
{
    m_separators = separators;
}

//! Set the start line
void DataImport::LineBlock::setName(std::string name)
{
    m_name = name;
}

//! Set the start line
void DataImport::LineBlock::setActive(bool active)
{
    m_active = active;
}

//! Set the start line
void DataImport::LineBlock::setType(std::string type_string)
{
    m_type_string = type_string;
}

//! Set the start line
void DataImport::LineBlock::setSeparator(std::string separator_name)
{
    m_separator_str = separator_name;
    m_separator = m_separators->at(separator_name);
}

//! Set the start line
void DataImport::LineBlock::setColor(std::string color_string)
{
    m_color = color_string;
}

//! Set the start line
void DataImport::LineBlock::setStart(int start_line)
{
    m_start_line = start_line;
}

//! Set the end line
void DataImport::LineBlock::setEnd(int end_line)
{
    m_end_line = end_line;
}

// -------------------------------------------------
//! This is the constructor
DataImport::ImportLogic::ImportLogic() : QObject()
{
    initSeparators();
}

//! This is the slot for adding files into the local memory 
DataImport::LineBlock* DataImport::ImportLogic::addLineBlock(std::string name)
{
    auto temp = std::make_unique<DataImport::LineBlock>(name);
    temp->setSeparators(&m_separators);
    auto address = temp.get();
    m_line_blocks.push_back(std::move(temp));

    return address;
}

//! This is the method removing a particular block given its pointer
void DataImport::ImportLogic::removeLineBlock(DataImport::LineBlock* block_ptr)
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
std::string DataImport::ImportLogic::getPreview(int row) const
{
    auto thumbnail = m_files.at(row)->thumbnail();
    std::vector<std::string> color_scheme = getColorScheme(thumbnail.size());
    std::vector<char> separator_scheme = getSeparatorScheme(thumbnail.size());

    std::string output;
    for (int i = 0; i < thumbnail.size(); ++i)
    {   
        auto formated_line = thumbnail.at(i);
        if (separator_scheme.at(i) != '!'){
            auto temp_string_vec = DataImport::split(thumbnail.at(i), separator_scheme.at(i));
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

//! Get the names of all the LineBlocks in place
bool DataImport::ImportLogic::nameInBlocks(const std::string &name) const
{
    for (auto &line_block: m_line_blocks){
        if (name == line_block->name()) return true;
    }
    return false;
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
std::vector<std::string> DataImport::ImportLogic::getColorScheme(int length) const
{
    std::vector<std::string> output(length, "black");
    for (auto &line_block : m_line_blocks){
        line_block->processColors(output);
    }
    return output;
}

//! Get the separator scheme
std::vector<char> DataImport::ImportLogic::getSeparatorScheme(int length) const
{
    std::vector<char> output(length, '!');
    for (auto &line_block : m_line_blocks){
        line_block->processSeparator(output);
    }
    return output;
}
