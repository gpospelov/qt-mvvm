// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/topitemstreeview.h"
#include "mvvm/factories/viewmodelfactory.h"

namespace ModelView {
TopItemsTreeView::TopItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateTopItemsViewModel(model));
}

TopItemsTreeView::~TopItemsTreeView() = default;

} // namespace ModelView
