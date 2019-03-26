// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitemtags.h"
#include "sessionitemtag.h"
#include <stdexcept>

using namespace ModelView;

SessionItemTags::SessionItemTags() {}

SessionItemTags::~SessionItemTags()
{
    for (auto tag : m_tags)
        delete tag;
}

void SessionItemTags::registerTag(TagInfo tagInfo)
{
    if (exists(tagInfo.name()))
        throw std::runtime_error("SessionItemTags::registerTag() -> Error. Existing name '"
                                 + tagInfo.name() + "'");

    m_tags.push_back(new SessionItemTag(tagInfo));
}

bool SessionItemTags::exists(const std::string& tag_name) const
{
    for (auto tag : m_tags)
        if (tag->name() == tag_name)
            return true;
    return false;
}

SessionItemTag* SessionItemTags::itemTag(const std::string& tag_name) const
{
    for (auto tag : m_tags)
        if (tag->name() ==tag_name)
            return tag;

    return nullptr;
}
