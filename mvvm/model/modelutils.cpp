// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modelutils.h"

using namespace ModelView;

void Utils::DeleteItemFromModel(SessionItem* item)
{
    auto model = item->model();
    if (!model)
        return;

    auto [tag, row] = item->parent()->tagRowOfItem(item);
    model->removeItem(item->parent(), tag, row);
}
