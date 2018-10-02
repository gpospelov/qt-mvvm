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
#include "itemfactory.h"
#include <QUndoStack>

SessionModel::SessionModel(const std::string& model_type)
    : m_root_item(nullptr)
    , m_item_factory(new ItemFactory)
    , m_model_type(model_type)
{
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

SessionItem* SessionModel::insertNewItem(SessionItem* parent, int row)
{
    if (!parent)
        parent = m_root_item;

    auto result = m_item_factory->createItem();
    result->setModel(this);
    parent->insertItem(row, result);

    return result;
}

SessionItem* SessionModel::rootItem() const
{
    return m_root_item;
}

QVariant SessionModel::data(SessionItem* item) const
{
    return item->data();
}

bool SessionModel::setData(SessionItem* item, const QVariant& value)
{
    if (m_undoStack) {
        m_undoStack->push(new SetValueCommand(this, pathFromItem(item), value));
    } else {
        return item->setData(value);
    }

    return true;
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
    if (value)
        m_undoStack.reset(new QUndoStack);
    else
        m_undoStack.reset();
}

QUndoStack* SessionModel::undoStack() const
{
    return m_undoStack.get();
}

ItemFactory* SessionModel::factory()
{
    return m_item_factory.get();
}

void SessionModel::createRootItem()
{
    m_root_item = m_item_factory->createEmptyItem();
    m_root_item->setModel(this);
}
