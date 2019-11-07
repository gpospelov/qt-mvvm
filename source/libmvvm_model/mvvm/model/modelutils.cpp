// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/modelutils.h>

using namespace ModelView;

void Utils::DeleteItemFromModel(SessionItem* item)
{
    auto model = item->model();
    if (!model)
        return;

    auto [tag, row] = item->parent()->tagRowOfItem(item);
    model->removeItem(item->parent(), tag, row);
}
