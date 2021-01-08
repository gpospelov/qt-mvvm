// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sceneitems.h"
#include "mvvm/utils/reallimits.h"

namespace {
const std::string RegionOfInterestItemType = "RegionOfInterest";
}

namespace GraphicsProxy {

RegionOfInterestItem::RegionOfInterestItem() : ModelView::CompoundItem(RegionOfInterestItemType)
{
    addProperty(P_XLOW, 0.0)->setDisplayName("Xlow");
    addProperty(P_YLOW, 0.0)->setDisplayName("Ylow");
    addProperty(P_XUP, 0.0)->setDisplayName("Xup");
    addProperty(P_YUP, 0.0)->setDisplayName("Yup");
}

} // namespace GraphicsProxy
