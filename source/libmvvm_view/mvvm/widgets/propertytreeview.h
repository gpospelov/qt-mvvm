// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_PROPERTYTREEVIEW_H
#define MVVM_WIDGETS_PROPERTYTREEVIEW_H

#include "mvvm/widgets/itemstreeview.h"

namespace ModelView {

//! Widget holding standard QTreeView and intended for displaying all properties of given
//! SessionItem.

class MVVM_VIEW_EXPORT PropertyTreeView : public ItemsTreeView {
    Q_OBJECT

public:
    PropertyTreeView(QWidget* parent = nullptr);
    ~PropertyTreeView();

    void setItem(SessionItem* item);
};

} // namespace ModelView

#endif // MVVM_WIDGETS_PROPERTYTREEVIEW_H
