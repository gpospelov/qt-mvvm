// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_LINKEDITEM_H
#define MVVM_LINKEDITEM_H

#include "sessionitem.h"
#include "sessionmodel.h"

namespace ModelView
{

//! Item to store a link to other arbitrary item.

class CORE_EXPORT LinkedItem : public SessionItem
{
public:
    LinkedItem();

    template <typename T=SessionItem> T* linkedItem() const;
};

template <typename T> T* LinkedItem::linkedItem() const
{
    return model()
               ? dynamic_cast<T*>(model()->findItem(data(ItemDataRole::DATA).value<std::string>()))
               : nullptr;
}

} // namespace ModelView

#endif // MVVM_LINKEDITEM_H
