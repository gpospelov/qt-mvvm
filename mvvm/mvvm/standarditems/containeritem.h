// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CONTAINERITEM_H
#define MVVM_CONTAINERITEM_H

#include <mvvm/model/compounditem.h>

namespace ModelView
{

class Data1DItem;

/*!
@class ContainerItem
@brief Simple container to store any type of children.

Used as convenience item to create branch with uniform children beneath.
*/

class CORE_EXPORT ContainerItem : public CompoundItem
{
public:
    static inline const std::string T_ITEMS = "T_ITEMS";
    ContainerItem();
};

} // namespace ModelView

#endif // MVVM_CONTAINERITEM_H
