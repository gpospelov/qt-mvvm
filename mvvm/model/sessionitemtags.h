// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONITEMTAGS_H
#define SESSIONITEMTAGS_H

#include "global.h"
#include <vector>
#include <string>

namespace ModelView
{

class SessionItemContainer;
class TagInfo;
class SessionItem;

//! Container of SessionItem's stored according to their tags.

class CORE_EXPORT SessionItemTags
{
public:
    SessionItemTags();
    ~SessionItemTags();
    SessionItemTags(const SessionItemTags&) = delete;
    SessionItemTags& operator=(const SessionItemTags&) = delete;

    // tag

    void registerTag(TagInfo tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name) const;

    std::string defaultTag() const;

    int itemCount(const std::string& tag_name) const;

    // adding and removal

    bool insertItem(SessionItem* item, int index, const std::string& tag = {});

    SessionItem* takeItem(int index, const std::string& tag = {});

    // item access
    SessionItem* getItem(const std::string& tag, int index = 0) const;

    std::vector<SessionItem*> getItems(const std::string& tag = {}) const;

    std::vector<SessionItem*> allitems() const;

    std::pair<std::string, int> tagIndexOfItem(const SessionItem* item) const;

private:
    SessionItemContainer* container(const std::string& tag_name) const;
    SessionItemContainer* find_container(const std::string& tag_name) const;
    std::vector<SessionItemContainer*> m_containers;
    std::string m_default_tag;
};

} // namespace ModelView

#endif // SESSIONITEMTAGS_H
