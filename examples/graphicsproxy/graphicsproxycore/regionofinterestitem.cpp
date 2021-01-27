// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "regionofinterestitem.h"

namespace {
const std::string RegionOfInterestItemType = "RegionOfInterest";
const std::string P_XLOW = "P_XLOW";
const std::string P_YLOW = "P_YLOW";
inline const std::string P_XUP = "P_XUP";
inline const std::string P_YUP = "P_YUP";
} // namespace

namespace GraphicsProxy {

RegionOfInterestItem::RegionOfInterestItem() : ModelView::CompoundItem(RegionOfInterestItemType)
{
    addProperty(P_XLOW, 0.0)->setDisplayName("Xlow");
    addProperty(P_YLOW, 0.0)->setDisplayName("Ylow");
    addProperty(P_XUP, 0.0)->setDisplayName("Xup");
    addProperty(P_YUP, 0.0)->setDisplayName("Yup");
}

double RegionOfInterestItem::xLow() const
{
    return property<double>(P_XLOW);
}

void RegionOfInterestItem::setXLow(double value)
{
    setProperty(P_XLOW, value);
}

double RegionOfInterestItem::yLow() const
{
    return property<double>(P_YLOW);
}

void RegionOfInterestItem::setYLow(double value)
{
    setProperty(P_YLOW, value);
}

double RegionOfInterestItem::xUp() const
{
    return property<double>(P_XUP);
}

void RegionOfInterestItem::setXUp(double value)
{
    setProperty(P_XUP, value);
}

double RegionOfInterestItem::yUp() const
{
    return property<double>(P_YUP);
}

void RegionOfInterestItem::setYUp(double value)
{
    setProperty(P_YUP, value);
}

void RegionOfInterestItem::setCorners(double xlow, double ylow, double xup, double yup)
{
    setXLow(xlow);
    setYLow(ylow);
    setXUp(xup);
    setYUp(yup);
}

} // namespace GraphicsProxy
