// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitemtag.h"
#include "sessionitem.h"

using namespace ModelView;

SessionItemTag::SessionItemTag(ModelView::TagInfo tag_info) : m_tag_info(std::move(tag_info)) {}

SessionItemTag::~SessionItemTag()
{
    for (auto item : m_items)
        delete item;
}

//! Returns number of items in given tag.

int SessionItemTag::childrenCount() const
{
    return static_cast<int>(m_items.size());
}

//! Inserts item in a vector of children at given index, returns true in the case of success.
//! If index==-1 or index==childrenCount(), item will be appended at the end of the vector.
//! If item can't be inserted (wrong model type, wrong index or maximum number of items reached),
//! will return false.

bool SessionItemTag::insertItem(SessionItem* item, int index)
{
    int vec_index = insert_index(item, index);

    if (vec_index < 0)
        return false;

    m_items.insert(std::next(m_items.begin(), vec_index), item);
    return true;
}

SessionItem* SessionItemTag::takeItem(int index)
{
    if (minimum_reached())
        return nullptr;

    SessionItem* result = itemAt(index);
    if (result)
        m_items.erase(m_items.begin() + index);

    return result;
}

std::vector<SessionItem*> SessionItemTag::children() const
{
    return m_items;
}

//! Returns index of item in vector of items.
//! Returns -1 if item doesn't belong to us.

int SessionItemTag::indexOfItem(SessionItem* item) const
{
    auto pos = find(m_items.begin(), m_items.end(), item);
    return pos == m_items.end() ? -1 : static_cast<int>(std::distance(m_items.begin(), pos));
}

//! Returns item at given index. Returns nullptr if index is invalid.

SessionItem* SessionItemTag::itemAt(int index) const
{
    return index >= 0 && index < childrenCount() ? m_items[static_cast<size_t>(index)] : nullptr;
}

//! Returns the name of SessionItemTag.

std::string SessionItemTag::name() const
{
    return m_tag_info.name();
}

TagInfo SessionItemTag::tagInfo() const
{
    return m_tag_info;
}

//! Calculates insert index from given requested_index.
//! Returns -1 if item is not suitable for insertion.

int SessionItemTag::insert_index(const SessionItem* item, int requested_index) const
{
    if (maximum_reached() || requested_index > childrenCount() || !is_valid_item(item))
        return -1;

    if (requested_index < 0)
        return childrenCount();

    return requested_index;
}

//! Returns true if no more items are allowed.

bool SessionItemTag::maximum_reached() const
{
    return m_tag_info.max() != -1 && m_tag_info.max() == childrenCount();
}

//! Returns true if less items than now is not allowed.

bool SessionItemTag::minimum_reached() const
{
    return m_tag_info.min() != -1 && m_tag_info.min() == childrenCount();
}

//! Returns true if item's modelType is intended for this tag.

bool SessionItemTag::is_valid_item(const SessionItem* item) const
{
    return item && m_tag_info.isValidChild(item->modelType()) ? true : false;
}
