// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_PROPERTYITEM_H
#define MVVM_MODEL_PROPERTYITEM_H

#include <mvvm/model/sessionitem.h>

namespace ModelView
{

class RealLimits;

//! Holds single data property for complex SessionItems.

class CORE_EXPORT PropertyItem : public SessionItem
{
public:
    PropertyItem();

    SessionItem* setLimits(const RealLimits& value);
};

} // namespace ModelView

#endif // MVVM_MODEL_PROPERTYITEM_H
