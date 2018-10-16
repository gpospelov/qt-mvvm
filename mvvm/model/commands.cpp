// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "commands.h"
#include "sessionmodel.h"
#include "sessionitem.h"
#include "jsonmodel.h"
#include "itemfactory.h"
#include <QJsonObject>

SetValueCommand::SetValueCommand(SessionModel* model, Path path, const QVariant& value, int role,
                                 QUndoCommand* parent)
    : QUndoCommand(parent)
    , m_path(path)
    , m_model(model)
    , m_value(value)
    , m_role(role)
{

}

void SetValueCommand::undo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    item->setData(m_value, m_role);
    m_value = old;
}

void SetValueCommand::redo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    item->setData(m_value, m_role);
    m_value = old;
}

// ----------------------------------------------------------------------------

InsertNewItemCommand::InsertNewItemCommand(const model_type& modelType, SessionItem* parent, int row)
    : m_row(row)
    , m_model_type(modelType)
    , m_model(parent->model())
{
    m_parent_path = m_model->pathFromItem(parent);
}

void InsertNewItemCommand::undo()
{
    auto parent = m_model->itemFromPath(m_parent_path);
    delete parent->takeRow(m_row);
}

void InsertNewItemCommand::redo()
{
    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = m_model->factory()->createItem(m_model_type);
    parent->insertItem(m_row, child);
}


// ----------------------------------------------------------------------------

InsertRowCommand::InsertRowCommand(SessionItem* parent, int row, SessionItem* child)
    : m_row(row)
    , m_model(parent->model())
{
    Q_ASSERT(m_model);
    m_parent_path = m_model->pathFromItem(parent);

    JsonModel converter; // FIXME get converter from the model
    m_child_backup.reset(new QJsonObject);
    converter.item_to_json(child, *m_child_backup);
}

void InsertRowCommand::undo()
{
    auto parent = m_model->itemFromPath(m_parent_path);
    delete parent->takeRow(m_row);
}

void InsertRowCommand::redo()
{
    JsonModel converter; // FIXME get converter from the model
    auto parent = m_model->itemFromPath(m_parent_path);
    converter.json_to_item(*m_child_backup, parent, m_row);
}

// ----------------------------------------------------------------------------

RemoveRowCommand::RemoveRowCommand(SessionItem* parent, int row)
    : m_row(row)
    , m_model(parent->model())
{
    Q_ASSERT(m_model);
    m_parent_path = m_model->pathFromItem(parent);
}

void RemoveRowCommand::undo()
{
    JsonModel converter; // FIXME get converter from the model
    auto parent = m_model->itemFromPath(m_parent_path);
    converter.json_to_item(*m_child_backup, parent, m_row);
}

void RemoveRowCommand::redo()
{
    JsonModel converter; // FIXME get converter from the model
    m_child_backup.reset(new QJsonObject);

    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = parent->childAt(m_row);
    converter.item_to_json(child, *m_child_backup);

    delete parent->takeRow(m_row);
}
