// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionmodel.h"
#include "commands.h"
#include "commandservice.h"
#include "customvariants.h"
#include "itemmanager.h"
#include "itempool.h"
#include "itemutils.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "taginfo.h"

using namespace ModelView;

SessionModel::SessionModel(std::string model_type)
    : m_item_manager(std::make_unique<ItemManager>()), m_commands(std::make_unique<CommandService>(this)),
      m_model_type(std::move(model_type)), m_mapper(std::make_unique<ModelMapper>(this))
{
    m_item_manager->setItemPool(std::make_shared<ItemPool>());
    createRootItem();
}

SessionModel::~SessionModel()
{
    m_mapper->callOnModelDestroyed();
}

std::string SessionModel::modelType() const
{
    return m_model_type;
}

SessionItem* SessionModel::insertNewItem(const model_type& modelType, SessionItem* parent,
                                         const std::string& tag, int index)
{
    return m_commands->insertNewItem(modelType, parent, tag, index);
}

SessionItem* SessionModel::rootItem() const
{
    return m_root_item.get();
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
        result.prepend(Utils::IndexOfChild(current->parent(), current));
        current = current->parent();
    }
    return result;
}

//! Returns item from path.

SessionItem* SessionModel::itemFromPath(Path path)
{
    SessionItem* result(rootItem());
    for (const auto& x : path) {
        result = Utils::ChildAt(result, x);
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

const ItemManager* SessionModel::manager() const
{
    return m_item_manager.get();
}

//! Removes given row from parent.

void SessionModel::removeItem(SessionItem* parent, const std::string& tag, int row)
{
    m_commands->removeItem(parent, tag, row);
}

void SessionModel::register_item(SessionItem* item)
{
    m_item_manager->register_item(item);
    item->activate(); // activates buisiness logic
}

void SessionModel::unregister_item(SessionItem* item)
{
    m_item_manager->unregister_item(item);
}

ModelMapper* SessionModel::mapper()
{
    return m_mapper.get();
}

void SessionModel::createRootItem()
{
    m_root_item = m_item_manager->createRootItem();
    m_root_item->setModel(this);
    m_root_item->registerTag(TagInfo::universalTag("rootTag"), /*set_as_default*/ true);
}
