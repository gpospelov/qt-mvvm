// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/standardchildrenstrategies.h"
#include "mvvm/model/groupitem.h"
#include "mvvm/model/itemutils.h"

using namespace ModelView;

// ----------------------------------------------------------------------------

std::vector<SessionItem*> AllChildrenStrategy::children(const SessionItem* item) const
{
    // we returns all children, even if some marked as invisible
    return item ? item->children() : std::vector<SessionItem*>();
}

std::vector<SessionItem*> TopItemsStrategy::children(const SessionItem* item) const
{
    return item ? Utils::TopLevelItems(*item) : std::vector<SessionItem*>();
}

// ----------------------------------------------------------------------------

/*
PropertyItemsStrategy example: if group property has Cylinder active:

Particle
    ShapeGroup
        Sphere
            Radius
        Cylinder
            Height
            Radius

will become:
Particle
    ShapeGroup -> Cylinder
        Height
        Radius
*/

std::vector<SessionItem*> PropertyItemsStrategy::children(const SessionItem* item) const
{
    if (!item)
        return std::vector<SessionItem*>();

    auto group = dynamic_cast<const GroupItem*>(item);
    auto next_item = group ? group->currentItem() : item;
    return Utils::SinglePropertyItems(*next_item);
}

// ----------------------------------------------------------------------------

/*
PropertyItemsFlatStrategy example: if group property has Cylinder active:

Particle
    ShapeGroup
        Sphere
            Radius
        Cylinder
            Height
            Radius

will become:
Particle
    ShapeGroup -> Cylinder
    Height
    Radius
*/

std::vector<SessionItem*> PropertyItemsFlatStrategy::children(const SessionItem* item) const
{
    if (!item)
        return std::vector<SessionItem*>();

    if (auto group = dynamic_cast<const GroupItem*>(item); group)
        return Utils::SinglePropertyItems(*group->currentItem());

    std::vector<SessionItem*> result;
    for (auto child : Utils::SinglePropertyItems(*item)) {
        if (auto group_item = dynamic_cast<GroupItem*>(child); group_item) {
            result.push_back(group_item);
            for (auto sub_property : Utils::SinglePropertyItems(*group_item->currentItem()))
                result.push_back(sub_property);
        }
        else {
            result.push_back(child);
        }
    }

    return result;
}
