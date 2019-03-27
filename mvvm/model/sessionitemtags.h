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

    void registerTag(TagInfo tagInfo, bool set_as_default = false);

    bool exists(const std::string& tag_name) const;

    std::string defaultTag() const;

    std::vector<SessionItem*> items(const std::string& tag = {}) const;

    bool insertItem(SessionItem* item, int index, const std::string& tag = {});

private:
    SessionItemContainer* find_container(const std::string& tag_name) const;
    SessionItemContainer* container(const std::string& tag_name) const;
    std::vector<SessionItemContainer*> m_tags;
    std::string m_default_tag;
};

} // namespace ModelView

#endif // SESSIONITEMTAGS_H
