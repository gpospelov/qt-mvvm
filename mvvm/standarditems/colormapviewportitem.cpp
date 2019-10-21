// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapviewportitem.h"
#include "axisitems.h"
#include <algorithm>
#include <vector>

using namespace ModelView;

ColorMapViewportItem::ColorMapViewportItem() : ViewportItem(Constants::ColorMapViewportItemType)
{
    register_xy_axes();
    registerTag(TagInfo::universalTag(T_ITEMS, {Constants::ColorMapItemType}),
                /*set_default*/ true);
}

std::pair<double, double> ColorMapViewportItem::data_xrange() const
{
    return xAxis()->range();
}

std::pair<double, double> ColorMapViewportItem::data_yrange() const
{
    return yAxis()->range();
}
