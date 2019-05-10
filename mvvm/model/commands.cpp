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
#include "jsonitem.h"
#include "itemmanager.h"
#include <QJsonObject>

using namespace ModelView;

InsertNewItemCommand::InsertNewItemCommand(model_type modelType, SessionItem* parent,
                                           std::string tag, int row)
    : m_tag(std::move(tag)), m_row(row)
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
    delete parent->takeItem(m_tag, row);
    m_result = nullptr;
}

void InsertNewItemCommand::redo()
{
    auto parent = m_model->itemFromPath(m_parent_path);
    auto child = m_model->manager()->createItem(m_model_type).release();
    parent->insertItem(child, m_tag, m_row);
    m_result = child;
}

InsertNewItemCommand::result_t InsertNewItemCommand::result() const
{
    return m_result;
}
