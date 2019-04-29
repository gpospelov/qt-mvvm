// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComboProperty.h
//! @brief     Defines class ComboProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "externalproperty.h"

using namespace ModelView;

ExternalProperty::ExternalProperty() {}

ExternalProperty::ExternalProperty(const std::string& text, const QColor& color,
                                   const std::string& id)
    : m_text(text), m_color(color), m_identifier(id)
{
}

std::string ExternalProperty::text() const
{
    return m_text;
}

QColor ExternalProperty::color() const
{
    return m_color;
}

std::string ExternalProperty::identifier() const
{
    return m_identifier;
}

bool ExternalProperty::isValid() const
{
    if (m_identifier.empty() && m_text.empty() && !m_color.isValid())
        return false;

    return true;
}

bool ExternalProperty::operator==(const ExternalProperty& other) const
{
    return m_identifier == other.m_identifier && m_text == other.m_text && m_color == other.m_color;
}

bool ExternalProperty::operator!=(const ExternalProperty& other) const
{
    return !(*this == other);
}

bool ExternalProperty::operator<(const ExternalProperty& other) const
{
    return m_identifier < other.m_identifier && m_text < other.m_text
           && m_color.name() < other.m_color.name();
}
