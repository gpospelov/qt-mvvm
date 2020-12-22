// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/externalproperty.h"

using namespace ModelView;

ExternalProperty::ExternalProperty() = default;

ExternalProperty::ExternalProperty(std::string text, QColor color, std::string id)
    : m_text(std::move(text)), m_color(std::move(color)), m_identifier(std::move(id))
{
}

ExternalProperty ExternalProperty::undefined()
{
    return ExternalProperty("Undefined", QColor(Qt::red));
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
    return !(m_identifier.empty() && m_text.empty() && !m_color.isValid());
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
