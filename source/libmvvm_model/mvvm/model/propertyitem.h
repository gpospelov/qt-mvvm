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

#include "mvvm/model/sessionitem.h"

namespace ModelView {

class RealLimits;

//! Item to carry concrete editable entity (e.g. 'double' value with limits).
//! Intended for use as a child or CompountItem, not expected to have own children.

class MVVM_MODEL_EXPORT PropertyItem : public SessionItem {
public:
    PropertyItem();

    PropertyItem* setDisplayName(const std::string& name) override;

    PropertyItem* setLimits(const RealLimits& value);
};

} // namespace ModelView

#endif // MVVM_MODEL_PROPERTYITEM_H
