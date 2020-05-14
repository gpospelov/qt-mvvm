// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importlinefilter.h"
#include "importutils.h"

#include <sstream>

namespace DataImportLogic
{

//! This is the constructor of LineFilter
LineFilter::LineFilter(std::string name)
    : m_name(name), m_active(false), m_start_line(0), m_end_line(1), m_separator(' '),
      m_type_string("Data"), m_color("black")
{
}

//! Return only the keys of the separators
std::vector<std::string> LineFilter::separatorNames() const
{
    std::vector<std::string> output;
    for (auto const& element : *m_separators) {
        output.push_back(element.first);
    }

    return output;
}

//! Set the right colors in the vector
void LineFilter::processColors(std::vector<std::string>& color_vec) const
{
    if (!m_active)
        return;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (color_vec.size()) : (m_end_line);

    if (start > color_vec.size())
        return;

    for (int i = start; i < ((end < color_vec.size()) ? (end) : (color_vec.size())); ++i) {
        color_vec.at(i) = m_color;
    }
}

//! Set the right separator in the vector
void LineFilter::processSeparator(std::vector<char>& separator_vec) const
{
    if (!m_active)
        return;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (separator_vec.size()) : (m_end_line);

    if (start > separator_vec.size())
        return;

    for (int i = start; i < ((end < separator_vec.size()) ? (end) : (separator_vec.size())); ++i) {
        separator_vec.at(i) = m_separator;
    }
}

//! Set the right type to the vector
void LineFilter::processType(std::vector<std::string>& type_vec) const
{
    if (!m_active)
        return;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (type_vec.size()) : (m_end_line);

    if (start > type_vec.size())
        return;

    for (int i = start; i < ((end < type_vec.size()) ? (end) : (type_vec.size())); ++i) {
        type_vec.at(i) = m_type_string;
    }
}

//! Set the right type to the vector
void LineFilter::processIgnore(std::vector<std::vector<std::string>>& ignore_vec) const
{
    if (!m_active)
        return;

    int start = m_start_line;
    int end = (m_end_line == -1) ? (ignore_vec.size()) : (m_end_line);

    if (start > ignore_vec.size())
        return;

    for (int i = start; i < ((end < ignore_vec.size()) ? (end) : (ignore_vec.size())); ++i) {
        ignore_vec.at(i) = m_ignore_strings;
    }
}

//! Getter for the name
std::string LineFilter::name() const
{
    return m_name;
}

//! Getter for the active boolean
bool LineFilter::active() const
{
    return m_active;
}

//! Getter for the type string
std::string LineFilter::type() const
{
    return m_type_string;
}

//! Getter for the separator key string
std::string LineFilter::separator() const
{
    return m_separator_str;
}

//! Getter for the color string
std::string LineFilter::color() const
{
    return m_color;
}

//! Getter for ignore string
std::vector<std::string> LineFilter::ignoreStrings() const
{
    return m_ignore_strings;
}

//! Getter for ignore string
std::string LineFilter::ignoreString() const
{
    std::string output;
    for (const auto& piece : m_ignore_strings)
        output += piece;
    return output;
}

//! Getter for the starting line integer
int LineFilter::start() const
{
    return m_start_line;
}

//! Getter for the ending line integer
int LineFilter::end() const
{
    return m_end_line;
}

//! Build the separator string
void LineFilter::setSeparators(std::map<std::string, char>* separators)
{
    m_separators = separators;
}

//! Set the name
void LineFilter::setName(std::string name)
{
    m_name = name;
}

//! Set the active state
void LineFilter::setActive(bool active)
{
    m_active = active;
}

//! Set the type
void LineFilter::setType(std::string type_string)
{
    m_type_string = type_string;
}

//! Set the separator
void LineFilter::setSeparator(std::string separator_name)
{
    m_separator_str = separator_name;
    m_separator = m_separators->at(separator_name);
}

//! Set the color
void LineFilter::setColor(std::string color_string)
{
    m_color = color_string;
}

//! Set the ignore strings from a vector of strings
void LineFilter::setIgnoreStrings(std::vector<std::string>& ignore_strings)
{
    m_ignore_strings = ignore_strings;
}

//! Set the ignore strings from a single string
void LineFilter::setIgnoreString(std::string ignore_string)
{
    std::stringstream ss(ignore_string);
    std::vector<std::string> result;
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        result.push_back(substr);
    }
    setIgnoreStrings(result);
}

//! Set the start line
void LineFilter::setStart(int start_line)
{
    m_start_line = start_line;
}

//! Set the end line
void LineFilter::setEnd(int end_line)
{
    m_end_line = end_line;
}

} // namespace DataImportLogic
