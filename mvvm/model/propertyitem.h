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

#include "sessionitem.h"

namespace ModelView {

//! Holds single data property for complex SessionItems.

class CORE_EXPORT PropertyItem : public SessionItem
{
public:
    PropertyItem();
};

} // namespace ModelView

#endif // MVVM_PROPERTYITEM_H
