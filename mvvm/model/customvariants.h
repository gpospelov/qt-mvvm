// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CUSTOMVARIANTS_H
#define CUSTOMVARIANTS_H

#include "global.h"

//! Registrations and translations for custom variants.

#include <QMetaType>
#include <QVariant>
#include <string>
#include <vector>

namespace ModelView
{
namespace Utils
{

//! Converts custom variant to standard variant which Qt views will understand.
CORE_EXPORT QVariant toQtVariant(const QVariant& custom);

//! Converts Qt variant to custom variant on board of SessionItem.
CORE_EXPORT QVariant toCustomVariant(const QVariant& standard);

} // namespace Utils
} // namespace ModelView

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<double>)

#endif
