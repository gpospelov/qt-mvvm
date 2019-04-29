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

#ifndef MVVM_EXTERNALPROPERTY_H
#define MVVM_EXTERNALPROPERTY_H

#include "mvvm_global.h"
#include <QColor>
#include <QVariant>
#include <string>

namespace ModelView
{

//! Property for QVariant to carry text, color and identifier. Can be used to link items with each
//! other.

class CORE_EXPORT ExternalProperty
{
public:
    ExternalProperty();
    ExternalProperty(const std::string& text, const QColor& color, const std::string& id = {});

    std::string text() const;

    QColor color() const;

    std::string identifier() const;

    bool isValid() const;

    bool operator==(const ExternalProperty& other) const;
    bool operator!=(const ExternalProperty& other) const;
    bool operator<(const ExternalProperty& other) const;

private:
    std::string m_text;
    QColor m_color;
    std::string m_identifier;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::ExternalProperty)

#endif // MVVM_EXTERNALPROPERTY_H
