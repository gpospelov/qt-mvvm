// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/widgets/topitemstreeview.h>

namespace ModelView
{
TopItemsTreeView::TopItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Utils::CreateTopItemsViewModel(model));
}

TopItemsTreeView::~TopItemsTreeView() = default;

} // namespace ModelView
