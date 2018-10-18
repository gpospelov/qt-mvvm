// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionmodel.h"
#include "sessionitem.h"
#include "commands.h"
#include "itemmanager.h"
#include "commandservice.h"
#include "itempool.h"

SessionModel::SessionModel(const std::string& model_type)
    : m_root_item(nullptr)
    , m_commands(new CommandService(this))
    , m_item_manager(new ItemManager)
    , m_model_type(model_type)
{
    m_item_manager->setItemPool(std::shared_ptr<ItemPool>(new ItemPool));
    createRootItem();
}

SessionModel::~SessionModel()
{
    delete m_root_item;
}

std::string SessionModel::modelType() const
{
    return m_model_type;
}

SessionItem* SessionModel::insertNewItem(const model_type& modelType, SessionItem* parent, int row)
{
    return m_commands->insertNewItem(modelType, parent, row);
}

SessionItem* SessionModel::rootItem() const
{
    return m_root_item;
}

QVariant SessionModel::data(SessionItem* item, int role) const
{
    return item->data(role);
}

bool SessionModel::setData(SessionItem* item, const QVariant& value, int role)
{
    return m_commands->setData(item, value, role);
}

//! Returns path from item.

Path SessionModel::pathFromItem(SessionItem* item)
{
    Path result;

    SessionItem* current(item);
    while (current && current->parent()) {
        result.prepend(current->parent()->rowOfChild(current));
        current = current->parent();
    }

    return result;
}

//! Returns item from path.

SessionItem* SessionModel::itemFromPath(Path path)
{
    SessionItem* result(rootItem());
    for(const auto& x : path) {
        result = result->childAt(x);
        if (!result)
            break;
    }

    return result;
}

void SessionModel::setUndoRedoEnabled(bool value)
{
    m_commands->setUndoRedoEnabled(value);
}

void SessionModel::setCommandRecordPause(bool value)
{
    m_commands->setCommandRecordPause(value);
}

QUndoStack* SessionModel::undoStack() const
{
    return m_commands->undoStack();
}

ItemManager* SessionModel::manager()
{
    return m_item_manager.get();
}

//! Removes given row from parent.

void SessionModel::removeRow(SessionItem* parent, int row)
{
    m_commands->removeRow(parent, row);
}

void SessionModel::createRootItem()
{
    m_root_item = m_item_manager->createRootItem();
    m_root_item->setModel(this);
}
