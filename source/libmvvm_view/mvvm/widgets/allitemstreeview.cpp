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
#include <mvvm/widgets/allitemstreeview.h>

namespace ModelView
{
AllItemsTreeView::AllItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateDefaultViewModel(model));
}

AllItemsTreeView::~AllItemsTreeView() = default;

} // namespace ModelView
