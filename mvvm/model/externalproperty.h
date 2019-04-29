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
#include <QString>
#include <QVariant>
#include <string>
#include <vector>

namespace ModelView
{

class CORE_EXPORT ExternalProperty
{
public:
    explicit ExternalProperty();

    QString text() const;
    void setText(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    QString identifier() const;
    void setIdentifier(const QString& identifier);

    QPixmap pixmap() const;

    bool isValid() const;

    QVariant variant() const;

    bool operator==(const ExternalProperty& other) const;
    bool operator!=(const ExternalProperty& other) const;
    bool operator<(const ExternalProperty& other) const;

private:
    QString m_text;
    QColor m_color;
    QString m_identifier;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::ExternalProperty)

#endif // MVVM_EXTERNALPROPERTY_H
