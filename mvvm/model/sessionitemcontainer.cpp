// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitemcontainer.h"
#include "sessionitem.h"

using namespace ModelView;

SessionItemContainer::SessionItemContainer(ModelView::TagInfo tag_info) : m_tag_info(std::move(tag_info)) {}

SessionItemContainer::~SessionItemContainer()
{
    for (auto item : m_items)
        delete item;
}

//! Returns number of items in given tag.

int SessionItemContainer::itemCount() const
{
    return static_cast<int>(m_items.size());
}

//! Returns vector of items in this container.

std::vector<SessionItem*> SessionItemContainer::items() const
{
    return m_items;
}

//! Inserts item in a vector of children at given index, returns true in the case of success.
//! If index==-1 or index==childrenCount(), item will be appended at the end of the vector.
//! If item can't be inserted (wrong model type, wrong index or maximum number of items reached),
//! will return false.

bool SessionItemContainer::insertItem(SessionItem* item, int index)
{
    int vec_index = insert_index(item, index);

    if (vec_index < 0)
        return false;

    m_items.insert(std::next(m_items.begin(), vec_index), item);
    return true;
}

SessionItem* SessionItemContainer::takeItem(int index)
{
    if (minimum_reached())
        return nullptr;

    SessionItem* result = itemAt(index);
    if (result)
        m_items.erase(m_items.begin() + index);

    return result;
}

//! Returns index of item in vector of items.
//! Returns -1 if item doesn't belong to us.

int SessionItemContainer::indexOfItem(SessionItem* item) const
{
    auto pos = find(m_items.begin(), m_items.end(), item);
    return pos == m_items.end() ? -1 : static_cast<int>(std::distance(m_items.begin(), pos));
}

//! Returns item at given index. Returns nullptr if index is invalid.

SessionItem* SessionItemContainer::itemAt(int index) const
{
    return index >= 0 && index < itemCount() ? m_items[static_cast<size_t>(index)] : nullptr;
}

//! Returns the name of SessionItemTag.

std::string SessionItemContainer::name() const
{
    return m_tag_info.name();
}

TagInfo SessionItemContainer::tagInfo() const
{
    return m_tag_info;
}

//! Calculates insert index from given requested_index.
//! Returns -1 if item is not suitable for insertion.

int SessionItemContainer::insert_index(const SessionItem* item, int requested_index) const
{
    if (maximum_reached() || requested_index > itemCount() || !is_valid_item(item))
        return -1;

    if (requested_index < 0)
        return itemCount();

    return requested_index;
}

//! Returns true if no more items are allowed.

bool SessionItemContainer::maximum_reached() const
{
    return m_tag_info.max() != -1 && m_tag_info.max() == itemCount();
}

//! Returns true if less items than now is not allowed.

bool SessionItemContainer::minimum_reached() const
{
    return m_tag_info.min() != -1 && m_tag_info.min() == itemCount();
}

//! Returns true if item's modelType is intended for this tag.

bool SessionItemContainer::is_valid_item(const SessionItem* item) const
{
    return item && m_tag_info.isValidChild(item->modelType()) ? true : false;
}
