// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sceneitems.h"
#include <mvvm/utils/reallimits.h>

namespace
{
const std::string RegionOfInterestItemType = "RegionOfInterest";
}

using namespace ModelView;

RegionOfInterestItem::RegionOfInterestItem() : CompoundItem(RegionOfInterestItemType)
{
    addProperty(P_XLOW, 0.0)->setDisplayName("Xlow")->setLimits(RealLimits::limitless());
    addProperty(P_YLOW, 0.0)->setDisplayName("Ylow")->setLimits(RealLimits::limitless());
    addProperty(P_XUP, 0.0)->setDisplayName("Xup")->setLimits(RealLimits::limitless());
    addProperty(P_YUP, 0.0)->setDisplayName("Yup")->setLimits(RealLimits::limitless());
}
