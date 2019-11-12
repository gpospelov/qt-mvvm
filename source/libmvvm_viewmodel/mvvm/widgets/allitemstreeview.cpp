// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/widgets/allitemstreeview.h>

namespace ModelView
{
AllItemsTreeView::AllItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Utils::CreateDefaultViewModel(model));
}

AllItemsTreeView::~AllItemsTreeView() = default;

} // namespace ModelView
