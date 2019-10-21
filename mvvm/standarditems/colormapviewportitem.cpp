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
#include "colormapitem.h"
#include "data2ditem.h"
#include <algorithm>
#include <vector>

using namespace ModelView;

ColorMapViewportItem::ColorMapViewportItem() : ViewportItem(Constants::ColorMapViewportItemType)
{
    register_xy_axes();
    addProperty<ViewportAxisItem>(P_ZAXIS)->setDisplayName("Z axis");
    // for the moment allow only one ColorMapItem
    registerTag(TagInfo(T_ITEMS, 0, 1, {Constants::ColorMapItemType}), /*set_default*/ true);
}

ViewportAxisItem* ColorMapViewportItem::zAxis() const
{
    return item<ViewportAxisItem>(P_ZAXIS);
}

void ColorMapViewportItem::update_viewport()
{
    ViewportItem::update_viewport();
    update_data_range();
}

std::pair<double, double> ColorMapViewportItem::data_xrange() const
{
    return xAxis()->range();
}

std::pair<double, double> ColorMapViewportItem::data_yrange() const
{
    return yAxis()->range();
}

//! Updates zAxis to lower, upper values over all data points.

void ColorMapViewportItem::update_data_range()
{
    auto values = item<ColorMapItem>(T_ITEMS)->dataItem()->content();
    auto [lower, upper] = std::minmax_element(std::begin(values), std::end(values));
    zAxis()->set_range(*lower, *upper);
}
