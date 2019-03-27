// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "sessionitemtags.h"
#include "sessionitemcontainer.h"
#include <stdexcept>

using namespace ModelView;

SessionItemTags::SessionItemTags() {}

SessionItemTags::~SessionItemTags()
{
    for (auto tag : m_tags)
        delete tag;
}

void SessionItemTags::registerTag(TagInfo tagInfo, bool set_as_default)
{
    if (exists(tagInfo.name()))
        throw std::runtime_error("SessionItemTags::registerTag() -> Error. Existing name '"
                                 + tagInfo.name() + "'");

    m_tags.push_back(new SessionItemContainer(tagInfo));
    if (set_as_default)
        m_default_tag = tagInfo.name();
}

//! Returns true if container with such name exists.

bool SessionItemTags::exists(const std::string& tag_name) const
{
    for (auto tag : m_tags)
        if (tag->name() == tag_name)
            return true;
    return false;
}

//! Returns the name of the tag marked as default.

std::string SessionItemTags::defaultTagName() const
{
    return m_default_tag;
}

//! Returns container corresponding to given tag name.

SessionItemContainer* SessionItemTags::container(const std::string& tag_name) const
{
    for (auto tag : m_tags)
        if (tag->name() ==tag_name)
            return tag;

    return nullptr;
}
