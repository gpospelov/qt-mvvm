// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMCONTROLLER_H
#define MVVM_ITEMCONTROLLER_H

#include "mvvm_export.h"
#include <memory>

namespace ModelView
{

class SessionItem;

/*!
@class ItemController
@brief Controller to track time of life of SessionItem.
*/

class CORE_EXPORT ItemController
{
public:
    ItemController();
    virtual ~ItemController();

    void setItem(SessionItem* item);

    SessionItem* currentItem() const;

    virtual void subscribe();
private:
    struct ItemControllerPrivate;
    std::unique_ptr<ItemControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_ITEMCONTROLLER_H
