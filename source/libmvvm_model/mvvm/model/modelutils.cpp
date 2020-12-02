// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/interfaces/undostackinterface.h>
#include <mvvm/model/modelutils.h>

using namespace ModelView;

//! Removes and deletes item from its model.

void Utils::DeleteItemFromModel(SessionItem* item)
{
    auto model = item->model();
    if (!model)
        return;

    model->removeItem(item->parent(), item->tagRow());
}

//! Moves item up (decrements row of the item). Works on children belonging to single tag.

void Utils::MoveUp(SessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == 0)
        return; // item already at the top
    item->model()->moveItem(item, item->parent(), tagrow.prev());
}

//! Moves item down (increments row of the item). Works on children belonging to single tag.

void Utils::MoveDown(SessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == item->parent()->itemCount(tagrow.tag) - 1)
        return; // item already at the buttom
    item->model()->moveItem(item, item->parent(), tagrow.next());
}

void Utils::BeginMacros(const SessionItem* item, const std::string& macro_name)
{
    if (!item->model())
        return;

    if (auto stack = item->model()->undoStack(); stack)
        stack->beginMacro(macro_name);
}

void Utils::EndMacros(const SessionItem* item)
{
    if (!item->model())
        return;

    if (auto stack = item->model()->undoStack(); stack)
        stack->endMacro();
}
