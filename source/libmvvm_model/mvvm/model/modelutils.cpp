// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/modelutils.h"
#include "mvvm/interfaces/undostackinterface.h"
#include "mvvm/model/path.h"
#include <QJsonObject>

using namespace ModelView;

Path Utils::PathFromItem(const SessionItem* item)
{
    if (!item || !item->model())
        return {};

    Path result;
    const SessionItem* current(item);
    while (current && current->parent()) {
        result.prepend(Utils::IndexOfChild(current->parent(), current));
        current = current->parent();
    }
    return result;
}

SessionItem* Utils::ItemFromPath(const SessionModel& model, const Path& path)
{
    SessionItem* result(model.rootItem());
    for (const auto& x : path) {
        result = Utils::ChildAt(result, x);
        if (!result)
            break;
    }
    return result;
}

void Utils::PopulateEmptyModel(const JsonModelConverterInterface* converter,
                               const SessionModel& source, SessionModel& target)
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
    if (!item)
        return;
    BeginMacros(item->model(), macro_name);
}

void Utils::EndMacros(const SessionItem* item)
{
    if (!item)
        return;
    EndMacros(item->model());
}

void Utils::BeginMacros(const SessionModel* model, const std::string& macro_name)
{
    if (!model)
        return;
    if (auto stack = model->undoStack(); stack)
        stack->beginMacro(macro_name);
}

void Utils::EndMacros(const SessionModel* model)
{
    if (!model)
        return;
    if (auto stack = model->undoStack(); stack)
        stack->endMacro();
}
