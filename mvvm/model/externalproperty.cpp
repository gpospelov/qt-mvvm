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
#include <QPixmap>

using namespace ModelView;


ExternalProperty::ExternalProperty()
{}

QString ExternalProperty::text() const
{
    return m_text;
}

void ExternalProperty::setText(const QString& name)
{
    m_text = name;
}


QColor ExternalProperty::color() const
{
    return m_color;
}

void ExternalProperty::setColor(const QColor& color)
{
    m_color = color;
}

QString ExternalProperty::identifier() const {
    return m_identifier;
}

void ExternalProperty::setIdentifier(const QString& identifier)
{
    m_identifier = identifier;
}

QPixmap ExternalProperty::pixmap() const
{
    QPixmap pixmap(10,10);
    pixmap.fill(color());
    return pixmap;
}

//! Returns true if property is in valid state (i.e. have at least one member defined).

bool ExternalProperty::isValid() const
{
    if (m_identifier.isEmpty() && m_text.isEmpty() && !m_color.isValid())
        return false;

    return true;
}

QVariant ExternalProperty::variant() const
{
    QVariant variant;
    variant.setValue(*this);
    return variant;
}

bool ExternalProperty::operator==(const ExternalProperty& other) const
{
    if (m_identifier != other.m_identifier)
        return false;
    if (m_text != other.m_text)
        return false;
    if (m_color != other.m_color)
        return false;

    return true;
}

bool ExternalProperty::operator!=(const ExternalProperty& other) const
{
    return !(*this == other);
}

bool ExternalProperty::operator<(const ExternalProperty& other) const
{
    return m_identifier < other.m_identifier && m_text < other.m_text;
}

