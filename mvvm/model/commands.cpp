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
#include "itemmanager.h"
#include <QJsonObject>

using namespace ModelView;

SetValueCommand::SetValueCommand(SessionItem* item, QVariant value, int role)
    : m_value(std::move(value))
    , m_role(role)
    , m_model(item->model())
    , m_result(false)
{
    Q_ASSERT(m_model);
    m_path = m_model->pathFromItem(item);
    setText(QString("Set value %1").arg(m_value.toString()));
}

void SetValueCommand::undo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    m_result = item->setDataIntern(m_value, m_role);
    m_value = old;
}

void SetValueCommand::redo()
{
    auto item = m_model->itemFromPath(m_path);
    QVariant old = item->data(m_role);
    m_result = item->setDataIntern(m_value, m_role);
    m_value = old;
}

//! Returns result of the command, which is bool value denoting that the value was set succesfully.
//! The value 'false' means that the data is the same and no change was required.

SetValueCommand::result_t SetValueCommand::result() const
{
    return m_result;
}

// ----------------------------------------------------------------------------

InsertNewItemCommand::InsertNewItemCommand(model_type modelType, SessionItem* parent, int row,
                                           std::string tag)
    : m_row(row)
    , m_tag(std::move(tag))
    , m_model_type(std::move(modelType))
    , m_model(parent->model())
    , m_result(nullptr)
{
    m_parent_path = m_model->pathFromItem(parent);
    setText(QString("New item type:%1 row:%2, tag:%3").arg(
                QString::fromStdString(m_model_type), QString::number(m_row), QString::fromStdString(m_tag)));
}

void InsertNewItemCommand::undo()
{
    auto parent = m_model->itemFromPath(m_parent_path);

    int row = m_row < 0 ? static_cast<int>(parent->getItems(m_tag).size())-1 : m_row;

    delete parent->takeItem(row, m_tag); // FIXME revise negative row
    m_result = nullptr;
}

void InsertNewItemCommand::redo()
{
    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = m_model->manager()->createItem(m_model_type);
    parent->insertItem(child, m_row, m_tag);
    m_result = child;
}

InsertNewItemCommand::result_t InsertNewItemCommand::result() const
{
    return m_result;
}

// ----------------------------------------------------------------------------

RemoveItemCommand::RemoveItemCommand(SessionItem* parent, int row, std::string tag)
    : m_row(row)
    , m_tag(std::move(tag))
    , m_model(parent->model())
    , m_result(true)
{
    Q_ASSERT(m_model);
    m_parent_path = m_model->pathFromItem(parent);
    setText(QString("Remove item row:%2, tag:%3").arg(
                QString::number(m_row), QString::fromStdString(m_tag)));
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo()
{
    m_model->setCommandRecordPause(true);

    const auto& converter = m_model->manager()->converter();

    auto parent = m_model->itemFromPath(m_parent_path);
    converter.json_to_item(*m_child_backup, parent, m_row, m_tag);

    m_model->setCommandRecordPause(false);
}

void RemoveItemCommand::redo()
{
    m_model->setCommandRecordPause(true);

    const auto& converter = m_model->manager()->converter();
    m_child_backup = std::make_unique<QJsonObject>();

    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = parent->takeItem(m_row, m_tag);
    converter.item_to_json(child, *m_child_backup);
    delete child;

    m_model->setCommandRecordPause(false);
}

RemoveItemCommand::result_t RemoveItemCommand::result() const
{
    return m_result;
}
