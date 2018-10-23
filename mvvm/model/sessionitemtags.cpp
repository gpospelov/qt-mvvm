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
#include <stdexcept>

SessionItemTags::TagInfo::TagInfo() : min(0), max(-1), childCount(0) {}

//! Register tag with given parameters. Returns true in case of success. Returns
//! false if parameters are invalid or such tag was already registered.

bool SessionItemTags::registerTag(const QString& name, int min, int max,
                                  const QStringList& modelTypes)
{
    if (min < 0 || (min > max && max >= 0))
        return false;

    if (name.isEmpty() || isValid(name))
        return false;

    TagInfo info;
    info.name = name;
    info.min = min;
    info.max = max;
    info.modelTypes = modelTypes;

    m_tags.push_back(info);

    return true;
}

//! Returns true if there is a registered tag with such name.
//! If modelType is not empty, than an additional check is performed if tag is
//! intended for the given modelType.

bool SessionItemTags::isValid(const QString& tagName, const QString& modelType) const
{
    for (const auto& tag : m_tags) {
        if (tag.name == tagName) {
            if (modelType.isEmpty())
                return true;
            else
                return tag.modelTypes.isEmpty() ? true : tag.modelTypes.contains(modelType);
        }
    }

    return false;
}

//! Returns list of modelTypes the given tagName is intended for.

QStringList SessionItemTags::modelTypesForTag(const QString& tagName) const
{
    return isValid(tagName) ? tagInfo(tagName).modelTypes : QStringList();
}

//! Returns start index of given tagName corresponding to the index of SessionItem's m_children.

int SessionItemTags::tagStartIndex(const QString& tagName) const
{
    int index(0);
    for (const auto& tag : m_tags) {
        if (tag.name == tagName)
            return index;
        else
            index += tag.childCount;
    }

    throw std::runtime_error("SessionItemTags::tagStartIndex() -> Error. Can';t find start index");
}

//! Returns index in SessionItem's m_children corresponding to given row in tagName.

int SessionItemTags::indexFromTagRow(const QString& tagName, int row) const
{
    auto& tag = tagInfo(tagName);

    if (row < 0 || row >= tag.childCount)
        throw std::runtime_error("SessionItemTags::tagIndexFromRow() -> Error. Wrong row");

    return tagStartIndex(tagName) + row;
}

//! Returns index in SessionItem's m_children to insert new item.
//! If number of items for given tagName exceeds maximum allowed, returns -1;

int SessionItemTags::insertIndexFromTagRow(const QString& tagName, int row)
{
    if (maximumReached(tagName))
        return -1;

    auto& tag = tagInfo(tagName);

    if (row > tag.childCount)
        return -1;

    if (row < 0)
        row = tag.childCount;

    return tagStartIndex(tagName) + row;
}

QString SessionItemTags::tagFromIndex(int index) const
{
    if (index < 0)
        return QString();

    for (const auto& tag : m_tags) {
        if (index < tag.childCount)
            return tag.name;
        else
            index -= tag.childCount;
    }

    return QString();
}

int SessionItemTags::childCount(const QString& tagName)
{
    return tagInfo(tagName).childCount;
}

int SessionItemTags::childMax(const QString& tagName)
{
    return tagInfo(tagName).max;
}

void SessionItemTags::addChild(const QString& tagName)
{
    if (maximumReached(tagName))
        throw std::runtime_error("SessionItemTags::addChild() -> Error. Can't exceed maximum"
                                "allowed number of children.");

    tagInfo(tagName).childCount++;
}

void SessionItemTags::removeChild(const QString& tagName)
{
    auto& tag = tagInfo(tagName);

    if (tag.childCount == 0)
        throw std::runtime_error("SessionItemTags::removeChild() -> Error. Attempt to remove "
                                "unexisting child.");

    tag.childCount--;
}

bool SessionItemTags::isSingleItemTag(const QString& tagName)
{
    if (!isValid(tagName))
        return false;

    auto& tag = tagInfo(tagName);
    return tag.min == 1 && tag.max == 1 && tag.childCount == 1;
}

SessionItemTags::TagInfo& SessionItemTags::tagInfo(const QString& tagName)
{
    return const_cast<TagInfo&>(static_cast<const SessionItemTags*>(this)->tagInfo(tagName));
}

const SessionItemTags::TagInfo& SessionItemTags::tagInfo(const QString& tagName) const
{
    for (const auto& tag : m_tags)
        if (tag.name == tagName)
            return tag;

    QString message = "SessionItemTags::tagInfo() -> Error. No such tag '" + tagName + "'.";
    throw std::runtime_error(message.toStdString());
}

bool SessionItemTags::maximumReached(const QString& tagName) const
{
    auto& tag = tagInfo(tagName);

    if (tag.max != -1 && tag.max == tag.childCount)
        return true;

    return false;
}
