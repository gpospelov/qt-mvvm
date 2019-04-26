// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWITEMS_H
#define MVVM_VIEWITEMS_H

#include "viewitem.h"

namespace ModelView
{

class SessionItem;

//! An empty item which will serve as a clone prototype for QStandardItemModel.
//! Normally shouldn't appear in views if ViewModel has correct cell edit permissions.

class CORE_EXPORT ViewEmptyItem : public ViewItem
{
public:
    explicit ViewEmptyItem();
    int type() const override;

    QVariant data(int role) const override;

    ViewEmptyItem* clone() const override;
};

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewLabelItem : public ViewItem
{
public:
    explicit ViewLabelItem(SessionItem* item);
    int type() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWITEMS_H
