// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SESSIONITEMCONTAINER_H
#define MVVM_SESSIONITEMCONTAINER_H

#include "mvvm_export.h"
#include "taginfo.h"
#include <vector>

namespace ModelView
{

class SessionItem;

//! Holds collection of SessionItem objects related to the same tag.

class CORE_EXPORT SessionItemContainer
{
public:
    using container_t = std::vector<SessionItem*>;
    using const_iterator = container_t::const_iterator;

    SessionItemContainer(TagInfo tag_info);
    SessionItemContainer(const SessionItemContainer&) = delete;
    SessionItemContainer& operator=(const SessionItemContainer&) = delete;
    ~SessionItemContainer();

    int itemCount() const;

    std::vector<SessionItem*> items() const;

    bool insertItem(SessionItem* item, int index);

    SessionItem* takeItem(int index);

    bool canTakeItem(int index) const;

    bool canInsertItem(const SessionItem* item, int index) const;

    int indexOfItem(const SessionItem* item) const;

    SessionItem* itemAt(int index) const;

    std::string name() const;

    TagInfo tagInfo() const;

    const_iterator begin() const;

    const_iterator end() const;

private:
    bool maximum_reached() const;
    bool minimum_reached() const;
    bool is_valid_item(const SessionItem* item) const;
    TagInfo m_tag_info;
    container_t m_items;
};

} // namespace ModelView

#endif // MVVM_SESSIONITEMCONTAINER_H
