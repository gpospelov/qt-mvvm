// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/commands/commandservice.h>
#include <mvvm/factories/itemcataloguefactory.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/itemfactory.h>
#include <mvvm/model/itemmanager.h>
#include <mvvm/model/itempool.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/model/tagrow.h>
#include <mvvm/signals/modelmapper.h>

using namespace ModelView;

SessionModel::SessionModel(std::string model_type, std::shared_ptr<ItemPool> pool)
    : m_model_type(std::move(model_type))
    , m_item_manager(std::make_unique<ItemManager>())
    , m_commands(std::make_unique<CommandService>(this))
    , m_mapper(std::make_unique<ModelMapper>(this))
{
    if (pool)
        m_item_manager->setItemPool(std::move(pool));
    else
        m_item_manager->setItemPool(std::make_shared<ItemPool>());
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
                                         const TagRow& tagrow)
{
    // intentionally passing by value inside lambda
    auto create_func = [this, modelType]() { return factory()->createItem(modelType); };
    return intern_insert(create_func, parent, tagrow);
}

//! Copy item and insert it in parent's tag and row.
//! Item could belong to any model/parent.

SessionItem* SessionModel::copyItem(const SessionItem* item, SessionItem* parent,
                                    const TagRow& tagrow)
{
    return m_commands->copyItem(item, parent, tagrow);
}

SessionItem* SessionModel::rootItem() const
{
    return m_root_item.get();
}

Variant SessionModel::data(SessionItem* item, int role) const
{
    return item->data<Variant>(role);
}

bool SessionModel::setData(SessionItem* item, const Variant& value, int role)
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

SessionItem* SessionModel::itemFromPath(const Path& path) const
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

UndoStackInterface* SessionModel::undoStack() const
{
    return m_commands->undoStack();
}

//! Removes given row from parent.

void SessionModel::removeItem(SessionItem* parent, const TagRow& tagrow)
{
    m_commands->removeItem(parent, tagrow);
}

//! Move item from it's current parent to a new parent under given tag and row.
//! Old and new parents should belong to this model.

void SessionModel::moveItem(SessionItem* item, SessionItem* new_parent, const TagRow& tagrow)
{
    m_commands->moveItem(item, new_parent, tagrow);
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

//! Removes all items from the model. If callback is provided, use it to rebuild content of root
//! item. Used while restoring the model from serialized content.

void SessionModel::clear(std::function<void(SessionItem*)> callback)
{
    mapper()->callOnModelAboutToBeReset();
    createRootItem();
    if (callback)
        callback(rootItem());
    mapper()->callOnModelReset();
}

//! Returns pointer to ItemFactory which can generate all items supported by this model,

const ItemFactoryInterface* SessionModel::factory() const
{
    return m_item_manager->factory();
}

//! Returns SessionItem for given identifier.

SessionItem* SessionModel::findItem(const identifier_type& id)
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

SessionItem* SessionModel::intern_insert(const item_factory_func_t& func, SessionItem* parent,
                                         const TagRow& tagrow)
{
    return m_commands->insertNewItem(func, parent, tagrow);
}
