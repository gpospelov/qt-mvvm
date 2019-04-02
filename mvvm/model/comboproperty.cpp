// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComboProperty.cpp
//! @brief     Implements class ComboProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "comboproperty.h"
#include <stdexcept>

namespace {
const QString value_separator = ";";
const QString selection_separator = ",";
}

ComboProperty::ComboProperty() = default;

ComboProperty::ComboProperty(QStringList values)
    : m_values(std::move(values))
{

}

ComboProperty ComboProperty::fromList(const QStringList& values, const QString& current_value)
{
    ComboProperty result(values);

    if (!current_value.isEmpty())
        result.setValue(current_value);

    return result;
}

QString ComboProperty::getValue() const
{
    return currentIndex() < 0 ? QString() : m_values.at(currentIndex());
}

void ComboProperty::setValue(const QString& name)
{
    if (!m_values.contains(name))
        throw std::runtime_error("ComboProperty::setValue() -> Error. Combo doesn't contain "
                                "value " + name.toStdString());
    setCurrentIndex(m_values.indexOf(name));
}

QStringList ComboProperty::getValues() const
{
    return m_values;
}

//! Sets new list of values. Current value will be preserved, if exists in a new list.

void ComboProperty::setValues(const QStringList& values)
{
    Q_ASSERT(values.size());
    QString current = getValue();
    m_values = values;
   setCurrentIndex(m_values.contains(current) ? m_values.indexOf(current) : 0);
}

//! returns list of tool tips for all values
QStringList ComboProperty::toolTips() const
{
    return m_tooltips;
}

void ComboProperty::setToolTips(const QStringList& tooltips)
{
    m_tooltips = tooltips;
}

int ComboProperty::currentIndex() const
{
    return m_selected_indices.empty() ? -1 : m_selected_indices.at(0);
}

void ComboProperty::setCurrentIndex(int index)
{
    if (index < 0 || index >= m_values.size())
        throw std::runtime_error("ComboProperty::setCurrentIndex(int index) -> Error. "
                                "Invalid index");
    m_selected_indices.clear();
    m_selected_indices.push_back(index);
}

ComboProperty& ComboProperty::operator<<(const QString& str)
{
    m_values.append(str);
    if (m_values.size())
        setCurrentIndex(0);
    return *this;
}

ComboProperty& ComboProperty::operator<<(const QStringList& str)
{
    m_values.append(str);
    if (m_values.size())
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
    return m_selected_indices.size() < other.m_selected_indices.size() && m_values.size() < other.m_values.size();
}

//! Returns a single string containing values delimited with ';'.

QString ComboProperty::stringOfValues() const
{
    return m_values.join(value_separator);
}

//! Sets values from the string containing delimeter ';'.

void ComboProperty::setStringOfValues(const QString& values)
{
    QString current = getValue();
    m_values = values.split(value_separator);
    setCurrentIndex(m_values.contains(current) ? m_values.indexOf(current) : 0);
}

//! Constructs variant enclosing given ComboProperty.

QVariant ComboProperty::variant() const
{
    QVariant result;
    result.setValue(*this);
    return result;
}

//! Returns vector of selected indices.

std::vector<int> ComboProperty::selectedIndices() const
{
    return m_selected_indices;
}

//! Returns list of string with selected values;

QStringList ComboProperty::selectedValues() const
{
    QStringList result;
    for (auto index : m_selected_indices)
        result.append(m_values.at(index));
    return result;
}

//! Sets given index selection flag.
//! If false, index will be excluded from selection.

void ComboProperty::setSelected(int index, bool value)
{
    if (index < 0 || index >= m_values.size())
        return;

    auto pos = find(m_selected_indices.begin(), m_selected_indices.end(), index);
    if (value) {
        if (pos == m_selected_indices.end())
            m_selected_indices.push_back(index);
    } else {
        if (pos != m_selected_indices.end())
            m_selected_indices.erase(pos);
    }
    std::sort(m_selected_indices.begin(), m_selected_indices.end());
}

void ComboProperty::setSelected(const QString& name, bool value)
{
    setSelected(m_values.indexOf(name), value);
}

//! Return string with coma separated list of selected indices.

QString ComboProperty::stringOfSelections() const
{
    QStringList text;
    for (auto  index : m_selected_indices)
        text.append(QString::number(index));
    return text.join(selection_separator);
}

//! Sets selected indices from string.

void ComboProperty::setStringOfSelections(const QString& values)
{
    m_selected_indices.clear();
    if (values.isEmpty())
        return;

    for (auto str : values.split(selection_separator)) {
        bool success(false);
        int num = str.toInt(&success);
        if (success)
            setSelected(num, true);
    }
}

//! Returns the label to show

QString ComboProperty::label() const
{
    if (m_selected_indices.size() >1) {
        return QStringLiteral("Multiple");
    } else if (m_selected_indices.size() == 1) {
        return getValue();
    } else {
        return QStringLiteral("None");
    }
}

