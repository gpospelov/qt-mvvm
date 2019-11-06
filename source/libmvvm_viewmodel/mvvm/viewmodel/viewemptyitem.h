// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWEMPTYITEM_H
#define MVVM_VIEWMODEL_VIEWEMPTYITEM_H

#include <mvvm/viewmodel/viewitem.h>

namespace ModelView
{

class SessionItem;

//! An empty item which serve as a clone prototype for QStandardItemModel.

class CORE_EXPORT ViewEmptyItem : public ViewItem
{
public:
    ViewEmptyItem();
    int type() const override;

    QVariant data(int role) const override;

    ViewEmptyItem* clone() const override;
};

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_VIEWEMPTYITEM_H
