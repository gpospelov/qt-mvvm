// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "customvariants.h"
#include "jsonvariant.h"

QVariant ModelView::toQtVariant(const QVariant& custom)
{
    // converts variant based on std::string to variant based on QString
    if (custom.typeName() == JsonVariant::string_type_name)
        return QVariant(QString::fromStdString(custom.value<std::string>()));

    // in other cases returns unchanged variant
    return custom;
}

QVariant ModelView::toCustomVariant(const QVariant& standard)
{
    const QString qstring_name = "QString";

    // converts variant based on std::string to variant based on QString
    if (standard.typeName() == qstring_name)
        return QVariant::fromValue(standard.toString().toStdString());

    // in other cases returns unchanged variant
    return standard;
}
