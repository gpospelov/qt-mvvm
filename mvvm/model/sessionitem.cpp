// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitem.h"
#include <stdexcept>
#include <iterator>

SessionItem::SessionItem()
    : m_parent(nullptr)
    , m_model(nullptr)
{

}

SessionItem::~SessionItem()
{
    for (auto item : m_children) {
        if (item)
            item->setModel(nullptr);
        delete item;
    }
    m_children.clear();
    if (m_parent)
        m_parent->childDeleted(this);
}

bool SessionItem::setData(QVariant data)
{
    m_data = data;
    return true;
}

QVariant SessionItem::data() const
{
    return m_data;
}

SessionModel* SessionItem::model() const
{
    return m_model;
}

SessionItem* SessionItem::parent() const
{
    return m_parent;
}

int SessionItem::childrenCount() const
{
    return static_cast<int>(m_children.size());
}

bool SessionItem::insertItem(int row, SessionItem* item)
{
    if (!item)
        throw std::runtime_error("SessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("SessionItem::insertItem() -> Existing parent.");

    if ( row < 0)
        row = childrenCount();

    if ( row > childrenCount())
        throw std::runtime_error("SessionItem::insertItem() -> Invalid index.");

    item->setParent(this);
    item->setModel(model());
    m_children.insert(std::next(m_children.begin(), row), item);

    return true;
}

std::vector<SessionItem*> SessionItem::children() const
{
    return m_children;
}

SessionItem* SessionItem::childAt(int row) const
{
    return row >= 0 && row < childrenCount() ? m_children[static_cast<size_t>(row)] : nullptr;
}

int SessionItem::rowOfChild(SessionItem* child) const
{
    auto pos = find(m_children.begin(), m_children.end(), child);
    return pos == m_children.end() ? -1 : static_cast<int>(std::distance(m_children.begin(), pos));
}

//! Removes row from item and returns the item.

SessionItem* SessionItem::takeRow(int row)
{
    SessionItem* result(nullptr);

    if (row >=0 && row < childrenCount()) {
        m_children.erase(m_children.begin() + row);
        auto result = childAt(row);
        if (result)
            result->setParent(nullptr);
    }
    return result;
}

void SessionItem::setParent(SessionItem* parent)
{
    m_parent = parent;
}

void SessionItem::setModel(SessionModel* model)
{
    m_model = model;

    for (auto child : m_children)
        child->setModel(model);
}

void SessionItem::childDeleted(SessionItem* child)
{
    auto index = rowOfChild(child);
    assert(index != -1);
    m_children[static_cast<size_t>(index)] = nullptr;
}
