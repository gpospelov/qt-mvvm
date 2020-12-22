// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_LINKEDITEM_H
#define MVVM_STANDARDITEMS_LINKEDITEM_H

#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"

namespace ModelView {

//! Item to store a persistent link to other arbitrary items.

//! The identifier of the item intended for linking is stored as DataRole on board of LinkedItem
//! and can be used to find the corresponding item via SessionModel::findItem machinery.
//! Provided mechanism is persistent and outlive serialization. Can be used to find items in
//! different models. For that being the case, models should use same ItemPool.

class MVVM_MODEL_EXPORT LinkedItem : public SessionItem {
public:
    LinkedItem();

    void setLink(const SessionItem* item);

    template <typename T = SessionItem> T* get() const;
};

//! Returns item linked to given item. Works only in model context.

template <typename T> T* LinkedItem::get() const
{
    return model() ? dynamic_cast<T*>(model()->findItem(data<std::string>())) : nullptr;
}

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_LINKEDITEM_H
