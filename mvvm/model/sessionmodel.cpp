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

SessionModel::SessionModel()
    : m_root_item(nullptr)
{
    createRootItem();
}

SessionModel::~SessionModel()
{
    delete m_root_item;
}

SessionItem* SessionModel::insertNewItem(SessionItem* parent, int row)
{
    if (!parent)
        parent = m_root_item;

    auto result = new SessionItem;
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
    return item->setData(value);
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

void SessionModel::createRootItem()
{
    m_root_item = new SessionItem;
    m_root_item->setModel(this);
}
