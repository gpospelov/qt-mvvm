// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/serialization/compatibilityutils.h>
#include <set>

namespace ModelView
{
namespace Compatibility
{

/*
This function allows us to combine two SessionItemData entities obtained via two different
mechanisms. `Runtime` is the data that SessionItem receives by default when created via
"new SessionItem", i.e during the lifetime of the GUI. It contains item identifier, data role,
display role, tooltips role, etc.

`Persistent` is the data obtained after restoring an item from disk. It contains some of the item
roles, from possibly much earlier moment, when the item has been saved.

The goal is to merge certain roles from `persistent` source with certain roles of `runtime` source.

For example, `tooltip` role is not intended for serialization, so it will be taken from `runtime`
source, while data role, will be taken from the saved copy.
*/

std::unique_ptr<SessionItemData> CombineItemData(const SessionItemData& runtime,
                                                 const SessionItemData& persistent)
{
    std::unique_ptr<SessionItemData> result = std::make_unique<SessionItemData>();

    auto runtime_roles = runtime.roles();
    auto persistent_roles = persistent.roles();

    std::set<int> roles(runtime_roles.begin(), runtime_roles.end());
    roles.insert(persistent_roles.begin(), persistent_roles.end());

    for (auto role : roles) {
        // all roles existing in `persistent` will be taken from there
        // the order of roles will be as in `runtime`
        if (persistent.hasData(role))
            result->setData(persistent.data(role), role);
        else
            result->setData(runtime.data(role), role);
    }

    return result;
}

/*


*/

bool IsCompatibleTagInfo(const SessionItemContainer& container, const TagInfo& taginfo)
{
    return false;
}

/*
Returns `true` if given TagInfo is a single property tag which is compatible with given container.
Here, `container` is what exists at runtime, `taginfo` has been obtained from the serialization.
Container is considered to be compatible (i.e. can be updated from serialized content), if it has
exactly same tag, and property item ready for update.
*/


bool IsCompatibleSinglePropertyTag(const SessionItemContainer& container, const TagInfo& taginfo)
{
    auto container_taginfo = container.tagInfo();

    bool has_item = !container.empty();
    bool both_are_properties =
        container_taginfo.isSinglePropertyTag() && taginfo.isSinglePropertyTag();
    bool same_tags = container_taginfo == taginfo;

    return both_are_properties && same_tags && has_item;
}

} // namespace Compatibility
} // namespace ModelView
