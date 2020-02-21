// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_REFVIEWITEMS_H
#define MVVM_VIEWMODEL_REFVIEWITEMS_H

#include <mvvm/viewmodel/refviewitem.h>

namespace ModelView
{

class SessionItem;

//! Represents root item.

class CORE_EXPORT RefRootViewItem : public RefViewItem
{
public:
    explicit RefRootViewItem(SessionItem* item);
};

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT RefViewLabelItem : public RefViewItem
{
public:
    explicit RefViewLabelItem(SessionItem* item);

    QVariant data(int role) const override;
};

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT RefViewDataItem : public RefViewItem
{
public:
    explicit RefViewDataItem(SessionItem* item);

    Qt::ItemFlags flags() const override;

};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWITEMS_H
