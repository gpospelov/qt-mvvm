// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/comboproperty.h"
#include "mvvm/utils/containerutils.h"
#include <sstream>
#include <stdexcept>

namespace {
const std::string value_separator = ";";
const std::string selection_separator = ",";
const std::string multiple_label = "Multiple";
const std::string none_label = "None";

template <typename C, typename T> std::string toString(const C& container, const T& delim)
{
    std::stringstream result;
    for (auto it = container.begin(); it != container.end(); ++it) {
        result << *it;
        if (std::distance(it, container.end()) != 1)
            result << delim;
    }
    return result.str();
}

std::vector<std::string> tokenize(const std::string& str, const std::string& delimeter)
{
    std::vector<std::string> result;
    size_t start = str.find_first_not_of(delimeter);
    size_t end = start;

    while (start != std::string::npos) {
        // Find next occurence of delimiter
        end = str.find(delimeter, start);
        // Push back the token found into vector
        result.push_back(str.substr(start, end - start));
        // Skip all occurences of the delimiter to find new start
        start = str.find_first_not_of(delimeter, end);
    }
    return result;
}
} // namespace

using namespace ModelView;

ComboProperty::ComboProperty() = default;

ComboProperty::ComboProperty(std::vector<std::string> values) : m_values(std::move(values)) {}

ComboProperty ComboProperty::createFrom(const std::vector<std::string>& values,
                                        const std::string& current_value)
{
    ComboProperty result(values);

    if (!current_value.empty())
        result.setValue(current_value);
    else
        result.setCurrentIndex(0);

    return result;
}

std::string ComboProperty::value() const
{
    return currentIndex() < 0 ? std::string() : m_values.at(static_cast<size_t>(currentIndex()));
}

void ComboProperty::setValue(const std::string& name)
{
    if (!Utils::Contains(m_values, name))
        throw std::runtime_error("ComboProperty::setValue() -> Error. Combo doesn't contain "
                                 "value "
                                 + name);
    setCurrentIndex(Utils::IndexOfItem(m_values, name));
}

std::vector<std::string> ComboProperty::values() const
{
    return m_values;
}

//! Sets new list of values. Current value will be preserved, if exists in a new list.

void ComboProperty::setValues(const std::vector<std::string>& values)
{
    if (values.empty())
        return;

    auto current = value();
    m_values = values;
    setCurrentIndex(Utils::Contains(m_values, current) ? Utils::IndexOfItem(m_values, current) : 0);
}

//! returns list of tool tips for all values
std::vector<std::string> ComboProperty::toolTips() const
{
    return m_tooltips;
}

void ComboProperty::setToolTips(const std::vector<std::string>& tooltips)
{
    m_tooltips = tooltips;
}

int ComboProperty::currentIndex() const
{
    return m_selected_indices.empty() ? -1 : m_selected_indices.at(0);
}

void ComboProperty::setCurrentIndex(int index)
{
    if (index < 0 || index >= static_cast<int>(m_values.size()))
        throw std::runtime_error("ComboProperty::setCurrentIndex(int index) -> Error. "
                                 "Invalid index");
    m_selected_indices.clear();
    m_selected_indices.push_back(index);
}

ComboProperty& ComboProperty::operator<<(const std::string& str)
{
    m_values.push_back(str);
    if (currentIndex() == -1)
        setCurrentIndex(0);
    return *this;
}

ComboProperty& ComboProperty::operator<<(const std::vector<std::string>& str)
{
    m_values.insert(m_values.end(), str.begin(), str.end());
    if (currentIndex() == -1)
        setCurrentIndex(0);
    return *this;
}

bool ComboProperty::operator==(const ComboProperty& other) const
{
    if (m_selected_indices != other.m_selected_indices)
        return false;
    if (m_values != other.m_values)
        return false;
    return true;
}

bool ComboProperty::operator!=(const ComboProperty& other) const
{
    return !(*this == other);
}

bool ComboProperty::operator<(const ComboProperty& other) const
{
    return m_selected_indices < other.m_selected_indices && m_values < other.m_values;
}

//! Returns a single string containing values delimited with ';'.

std::string ComboProperty::stringOfValues() const
{
    return toString(m_values, value_separator);
}

//! Sets values from the string containing delimeter ';'.

void ComboProperty::setStringOfValues(const std::string& values)
{
    auto current = value();
    m_values = tokenize(values, value_separator);
    setCurrentIndex(Utils::Contains(m_values, current) ? Utils::IndexOfItem(m_values, current) : 0);
}

//! Returns vector of selected indices.

std::vector<int> ComboProperty::selectedIndices() const
{
    return m_selected_indices;
}

//! Returns list of string with selected values;

std::vector<std::string> ComboProperty::selectedValues() const
{
    std::vector<std::string> result;
    for (auto index : m_selected_indices)
        result.push_back(m_values.at(static_cast<size_t>(index)));
    return result;
}

//! Sets given index selection flag.
//! If false, index will be excluded from selection.

void ComboProperty::setSelected(int index, bool value)
{
    if (index < 0 || index >= static_cast<int>(m_values.size()))
        return;

    auto pos = find(m_selected_indices.begin(), m_selected_indices.end(), index);
    if (value) {
        if (pos == m_selected_indices.end())
            m_selected_indices.push_back(index);
    }
    else {
        if (pos != m_selected_indices.end())
            m_selected_indices.erase(pos);
    }
    std::sort(m_selected_indices.begin(), m_selected_indices.end());
}

void ComboProperty::setSelected(const std::string& name, bool value)
{
    setSelected(Utils::IndexOfItem(m_values, name), value);
}

//! Return string with coma separated list of selected indices.

std::string ComboProperty::stringOfSelections() const
{
    std::vector<std::string> text;
    for (auto index : m_selected_indices)
        text.push_back(std::to_string(index));
    return toString(text, selection_separator);
}

//! Sets selected indices from string.

void ComboProperty::setStringOfSelections(const std::string& values)
{
    m_selected_indices.clear();
    if (values.empty())
        return;

    for (const auto& str : tokenize(values, selection_separator)) {
        int num = std::stoi(str);
        setSelected(num, true);
    }
}

//! Returns the label to show.

std::string ComboProperty::label() const
{
    if (m_selected_indices.size() > 1) {
        return multiple_label;
    }
    else if (m_selected_indices.size() == 1) {
        return value();
    }
    else {
        return none_label;
    }
}
