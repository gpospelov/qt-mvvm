// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PROPERTYITEM_H
#define MVVM_PROPERTYITEM_H

#include <mvvm/model/sessionitem.h>

namespace ModelView {

class RealLimits;

//! Holds single data property for complex SessionItems.

class CORE_EXPORT PropertyItem : public SessionItem
{
public:
    PropertyItem();

    SessionItem& setLimits(const RealLimits& value);

};

} // namespace ModelView

#endif // MVVM_PROPERTYITEM_H
