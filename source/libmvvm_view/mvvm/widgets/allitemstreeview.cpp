// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/allitemstreeview.h"
#include "mvvm/factories/viewmodelfactory.h"

namespace ModelView {
AllItemsTreeView::AllItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateDefaultViewModel(model));
}

AllItemsTreeView::~AllItemsTreeView() = default;

} // namespace ModelView
