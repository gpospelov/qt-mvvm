// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONITEMCONTAINER_H
#define SESSIONITEMCONTAINER_H

#include "global.h"
#include "taginfo.h"
#include <vector>

namespace ModelView
{

class SessionItem;

//! Holds collection of SessionItem objects related to the same tag.

class CORE_EXPORT SessionItemContainer
{
public:
    SessionItemContainer(TagInfo tag_info);
    SessionItemContainer(const SessionItemContainer&) = delete;
    SessionItemContainer& operator=(const SessionItemContainer&) = delete;
    ~SessionItemContainer();

    int childrenCount() const;

    bool insertItem(SessionItem* item, int index = -1);

    SessionItem* takeItem(int index);

    std::vector<SessionItem*> children() const;

    int indexOfItem(SessionItem* item) const;

    SessionItem* itemAt(int index) const;

    std::string name() const;

    TagInfo tagInfo() const;

private:
    int insert_index(const SessionItem* item, int requested_index) const;
    bool maximum_reached() const;
    bool minimum_reached() const;
    bool is_valid_item(const SessionItem* item) const;
    TagInfo m_tag_info;
    std::vector<SessionItem*> m_items;
};

} // namespace ModelView

#endif // SESSIONITEMCONTAINER_H
