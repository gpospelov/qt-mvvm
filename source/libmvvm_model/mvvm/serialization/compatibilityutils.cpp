// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/sessionitemdata.h>
#include <mvvm/serialization/compatibilityutils.h>

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

    for (const auto& x : runtime) {
        // all roles existing in `persistent` will be taken from there
        // the order of roles will be as in `runtime`
        if (persistent.hasData(x.m_role))
            result->setData(persistent.data(x.m_role), x.m_role);
        else
            result->setData(x.m_data, x.m_role);
    }

    return result;
}

} // namespace Compatibility
} // namespace ModelView
