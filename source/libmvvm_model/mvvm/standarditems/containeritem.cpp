// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/standarditems/containeritem.h>

using namespace ModelView;

ContainerItem::ContainerItem(const std::string& modelType) : CompoundItem(modelType)
{
    registerTag(ModelView::TagInfo::universalTag(T_ITEMS), /*set_as_default*/ true);
}

// FIXME implement empty() const and tests
