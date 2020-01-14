// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWDATAITEM_H
#define MVVM_VIEWMODEL_VIEWDATAITEM_H

#include <mvvm/viewmodel/viewitem.h>

namespace ModelView
{

class SessionItem;

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class CORE_EXPORT ViewDataItem : public ViewItem
{
public:
    explicit ViewDataItem(SessionItem* item);
    int type() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWDATAITEM_H
