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
#include "jsonitembackupstrategy.h"
#include "jsonitemcopystrategy.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "standarditemcatalogue.h"
#include "taginfo.h"

using namespace ModelView;

SessionModel::SessionModel(std::string model_type)
    : SessionModel(std::move(model_type), std::make_shared<ItemPool>())
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
                                         const std::string& tag, int row)
{
    auto create_func = [this, &modelType]() { return factory()->createItem(modelType); };
    return intern_insert(create_func, parent, tag, row);
}

//! Copy item and insert it in parent's tag and row.
//! Item could belong to any model/parent.

SessionItem* SessionModel::copyItem(const SessionItem* item, SessionItem* parent,
                                    const std::string& tag, int row)
{
    return m_commands->copyItem(item, parent, {tag, row});
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

//! Removes given row from parent.

void SessionModel::removeItem(SessionItem* parent, const std::string& tag, int row)
{
    m_commands->removeItem(parent, {tag, row});
}

//! Move item from it's current parent to a new parent under given tag and row.
//! Old and new parents should belong to this model.

void SessionModel::moveItem(SessionItem* item, SessionItem* new_parent, const std::string& tag,
                            int row)
{
    m_commands->moveItem(item, new_parent, {tag, row});
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
    createRootItem();
}

//! Returns strategy suitable for saving/restoring SessionItem.
//! Restored item will have same identifiers as original.

std::unique_ptr<ItemBackupStrategy> SessionModel::itemBackupStrategy() const
{
    return std::make_unique<JsonItemBackupStrategy>(factory());
}

//! Returns strategy for copying items.
//! Identifiers of the copy will be different from identifiers of the original.

std::unique_ptr<ItemCopyStrategy> SessionModel::itemCopyStrategy() const
{
    return std::make_unique<JsonItemCopyStrategy>(factory());
}

//! Returns pointer to ItemFactory which can generate all items supported by this model,

const ItemFactoryInterface* SessionModel::factory() const
{
    return m_item_manager->factory();
}

//!  Returns SessionItem for given identifier.

SessionItem* SessionModel::findItem(identifier_type id)
{
    return m_item_manager->findItem(id);
}

//! Creates root item.

void SessionModel::createRootItem()
{
    m_root_item = m_item_manager->createRootItem();
    m_root_item->setModel(this);
    m_root_item->registerTag(TagInfo::universalTag("rootTag"), /*set_as_default*/ true);
}

SessionItem* SessionModel::intern_insert(item_factory_func_t func, SessionItem* parent,
                                       const std::string& tag, int row)
{
    return m_commands->insertNewItem(func, parent, {tag, row});
}
