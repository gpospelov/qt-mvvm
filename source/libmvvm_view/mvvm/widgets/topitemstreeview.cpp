// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/widgets/topitemstreeview.h>

namespace ModelView
{
TopItemsTreeView::TopItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateTopItemsViewModel(model));
}

TopItemsTreeView::~TopItemsTreeView() = default;

} // namespace ModelView
