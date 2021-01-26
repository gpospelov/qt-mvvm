// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_ALLITEMSTREEVIEW_H
#define MVVM_WIDGETS_ALLITEMSTREEVIEW_H

#include "mvvm/widgets/itemstreeview.h"

namespace ModelView {

class SessionModel;

//! Widget holding standard QTreeView and intended for displaying all items of SessionModel.

class MVVM_VIEW_EXPORT AllItemsTreeView : public ItemsTreeView {
    Q_OBJECT

public:
    AllItemsTreeView(SessionModel* model, QWidget* parent = nullptr);
    ~AllItemsTreeView() override;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ALLITEMSTREEVIEW_H
