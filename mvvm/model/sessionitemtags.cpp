// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemTags.cpp
//! @brief     Implement class SessionItemTags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "sessionitemtags.h"
#include <algorithm>
#include <stdexcept>

using namespace ModelView;

//! Register tag with given parameters. Returns true in case of success. Returns
//! false if parameters are invalid or such tag was already registered.

bool SessionItemTags::registerTag(const std::string& name, int min, int max,
                                  const std::vector<std::string>& modelTypes)
{
    if (name.empty() || isValid(name))
        return false;

    m_tags.push_back(TagInfo(name, min, max, modelTypes));

    return true;
}

//! Returns true if there is a registered tag with such name.
//! If modelType is not empty, than an additional check is performed if tag is
//! intended for the given modelType.

bool SessionItemTags::isValid(const std::string& tagName, const std::string& modelType) const
{
    bool result(false);

    for (const auto& tag : m_tags) {
        if (tag.name() == tagName) {
            if (modelType.empty())
                result = true;
            else
                result = tag.isValidChild(modelType);
            break;
        }
    }

    return result;
}

//! Returns list of modelTypes the given tagName is intended for.

std::vector<std::string> SessionItemTags::modelTypesForTag(const std::string& tagName) const
{
    return isValid(tagName) ? tagInfo(tagName).modelTypes() : std::vector<std::string>();
}

//! Returns start index of given tagName corresponding to the index of SessionItem's m_children.

int SessionItemTags::tagStartIndex(const std::string& tagName) const
{
    int index(0);
    for (const auto& tag : m_tags) {
        if (tag.name() == tagName)
            return index;
        else
            index += tag.childCount();
    }

    throw std::runtime_error("SessionItemTags::tagStartIndex() -> Error. Can't find start index");
}

//! Returns index in SessionItem's m_children corresponding to given row in tagName.

int SessionItemTags::indexFromTagRow(const std::string& tagName, int row) const
{
    auto& tag = tagInfo(tagName);

    if (row < 0 || row >= tag.childCount())
        throw std::runtime_error("SessionItemTags::tagIndexFromRow() -> Error. Wrong row");

    return tagStartIndex(tagName) + row;
}

//! Returns index in SessionItem's m_children to insert new item.
//! If number of items for given tagName exceeds maximum allowed, returns -1;

int SessionItemTags::insertIndexFromTagRow(const std::string& tagName, int row)
{
    if (maximumReached(tagName))
        return -1;

    auto& tag = tagInfo(tagName);

    if (row > tag.childCount())
        return -1;

    if (row < 0)
        row = tag.childCount();

    return tagStartIndex(tagName) + row;
}

std::string SessionItemTags::tagFromIndex(int index) const
{
    if (index < 0)
        return {};

    for (const auto& tag : m_tags) {
        if (index < tag.childCount())
            return tag.name();
        else
            index -= tag.childCount();
    }

    return {};
}

int SessionItemTags::childCount(const std::string& tagName)
{
    return tagInfo(tagName).childCount();
}

void SessionItemTags::addChild(const std::string& tagName)
{
    tagInfo(tagName).add();
}

void SessionItemTags::removeChild(const std::string& tagName)
{
    tagInfo(tagName).remove();
}

bool SessionItemTags::isSingleItemTag(const std::string& tagName)
{
    return tagInfo(tagName).isSingleItemTag();
}

TagInfo& SessionItemTags::tagInfo(const std::string& tagName)
{
    return const_cast<TagInfo&>(static_cast<const SessionItemTags*>(this)->tagInfo(tagName));
}

const TagInfo& SessionItemTags::tagInfo(const std::string& tagName) const
{
    for (const auto& tag : m_tags)
        if (tag.name() == tagName)
            return tag;

    std::string message = "SessionItemTags::tagInfo() -> Error. No such tag '" + tagName + "'.";
    throw std::runtime_error(message);
}

bool SessionItemTags::maximumReached(const std::string& tagName) const
{
    return tagInfo(tagName).maximumReached();
}
