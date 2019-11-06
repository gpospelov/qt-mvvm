// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_LINKEDITEM_H
#define MVVM_STANDARDITEMS_LINKEDITEM_H

#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>

namespace ModelView
{

/*!
@class LinkedItem
@brief Item to store a link to other arbitrary item.

Identifier of linked item is stored as DataRole on board of LinkedItem and can be used
to find corresponding item via SessionModel::findItem machinery.
*/

class CORE_EXPORT LinkedItem : public SessionItem
{
public:
    LinkedItem();

    void setLink(const SessionItem* item);

    template <typename T=SessionItem> T* get() const;
};

//! Returns item linked to given item. Works only in model context.

template <typename T> T* LinkedItem::get() const
{
    return model()
               ? dynamic_cast<T*>(model()->findItem(data().value<std::string>()))
               : nullptr;
}

} // namespace ModelView

#endif  // MVVM_STANDARDITEMS_LINKEDITEM_H
