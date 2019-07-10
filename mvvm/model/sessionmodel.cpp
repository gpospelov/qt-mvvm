// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionmodel.h"
#include "commandservice.h"
#include "customvariants.h"
#include "itemcatalogue.h"
#include "itemfactory.h"
#include "itemmanager.h"
#include "itempool.h"
#include "itemutils.h"
#include "jsonbackupstrategy.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "standarditemcatalogue.h"
#include "taginfo.h"
#include "jsonitemcopystrategy.h"

using namespace ModelView;

SessionModel::SessionModel(std::string model_type)
    : SessionModel(model_type, std::make_shared<ItemPool>())
{
}

SessionModel::SessionModel(std::string model_type, std::shared_ptr<ItemPool> pool)
    : m_item_manager(std::make_unique<ItemManager>()),
      m_commands(std::make_unique<CommandService>(this)), m_model_type(std::move(model_type)),
      m_mapper(std::make_unique<ModelMapper>(this))
{
    m_item_manager->setItemPool(pool);
    createRootItem();
}

SessionModel::~SessionModel()
{
    m_mapper->callOnModelDestroyed();
}

void SessionModel::setItemCatalogue(std::unique_ptr<ItemCatalogue> catalogue)
{
    // adding standard items to the user catalogue
    std::unique_ptr<ItemCatalogue> full_catalogue = std::move(catalogue);
    full_catalogue->merge(*CreateStandardItemCatalogue());
    m_item_manager->setItemFactory(std::make_unique<ItemFactory>(std::move(full_catalogue)));
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

Path SessionModel::pathFromItem(const SessionItem* item) const
{
    Path result;
    const SessionItem* current(item);
    while (current && current->parent()) {
        result.prepend(Utils::IndexOfChild(current->parent(), current));
        current = current->parent();
    }
    return result;
}

//! Returns item from path.

SessionItem* SessionModel::itemFromPath(Path path) const
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

void SessionModel::moveItem(SessionItem* item, SessionItem* new_parent, const std::string& tag, int row)
{
    m_commands->moveItem(item, new_parent, tag, row);
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

//! Removes all items from the model.

void SessionModel::clear()
{
    mapper()->callOnModelReset();
    m_root_item.reset();
    createRootItem();
}

std::unique_ptr<ItemBackupStrategy> SessionModel::backupStrategy() const
{
    return std::make_unique<JsonBackupStrategy>(factory());
}

std::unique_ptr<SessionItem> SessionModel::createCopy(const SessionItem* item)
{
    if (item->model() != this)
        throw std::runtime_error("SessionModel::createCopy() -> Can't copy alien item");
    return JsonItemCopyStrategy(m_item_manager->factory()).createCopy(item);
}

const ItemFactoryInterface* SessionModel::factory() const
{
    return m_item_manager->factory();
}

void SessionModel::createRootItem()
{
    m_root_item = m_item_manager->createRootItem();
    m_root_item->setModel(this);
    m_root_item->registerTag(TagInfo::universalTag("rootTag"), /*set_as_default*/ true);
}
