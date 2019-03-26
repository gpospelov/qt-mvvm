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

class SessionItemTag;
class TagInfo;

//! Container of SessionItemTag.

class CORE_EXPORT SessionItemTags
{
public:
    SessionItemTags();
    ~SessionItemTags();
    SessionItemTags(const SessionItemTags&) = delete;
    SessionItemTags& operator=(const SessionItemTags&) = delete;

    void registerTag(TagInfo tagInfo);

    bool exists(const std::string& tag_name) const;

private:
    SessionItemTag* itemTag(const std::string& tag_name) const;
    std::vector<SessionItemTag*> m_tags;
};

} // namespace ModelView

#endif // SESSIONITEMTAGS_H
