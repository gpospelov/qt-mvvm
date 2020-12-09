// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonObject>
#include <mvvm/interfaces/undostackinterface.h>
#include <mvvm/model/modelutils.h>

using namespace ModelView;

void Utils::PopulateEmptyModel(const JsonModelConverterInterface* converter, const SessionModel& source, SessionModel& target)
{
    QJsonObject object = converter->to_json(source);
    converter->from_json(object, target);
}

void Utils::DeleteItemFromModel(SessionItem* item)
{
    auto model = item->model();
    if (!model)
        return;

    model->removeItem(item->parent(), item->tagRow());
}

void Utils::MoveUp(SessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == 0)
        return; // item already at the top
    item->model()->moveItem(item, item->parent(), tagrow.prev());
}

void Utils::MoveDown(SessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == item->parent()->itemCount(tagrow.tag) - 1)
        return; // item already at the buttom
    item->model()->moveItem(item, item->parent(), tagrow.next());
}

void Utils::Undo(SessionModel& model)
{
    if (auto stack = model.undoStack(); stack)
        stack->undo();
}

void Utils::Redo(SessionModel& model)
{
    if (auto stack = model.undoStack(); stack)
        stack->redo();
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
