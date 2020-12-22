// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/containeritem.h"

using namespace ModelView;

ContainerItem::ContainerItem(const std::string& modelType) : CompoundItem(modelType)
{
    registerTag(ModelView::TagInfo::universalTag(T_ITEMS), /*set_as_default*/ true);
}

bool ContainerItem::empty() const
{
    return childrenCount() == 0;
}

size_t ContainerItem::size() const
{
    return static_cast<size_t>(childrenCount());
}
