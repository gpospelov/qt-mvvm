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

namespace {
const std::pair<double, double> default_axis_range{0.0, 1.0};
}

using namespace ModelView;

ColorMapViewportItem::ColorMapViewportItem() : ViewportItem(Constants::ColorMapViewportItemType)
{
    register_xy_axes();
    addProperty<ViewportAxisItem>(P_ZAXIS)->setDisplayName("color-axis");
    // for the moment allow only one ColorMapItem
    registerTag(TagInfo(T_ITEMS, 0, 1, {Constants::ColorMapItemType}), /*set_default*/ true);
}

ViewportAxisItem* ColorMapViewportItem::colorAxis() const
{
    return item<ViewportAxisItem>(P_ZAXIS);
}

void ColorMapViewportItem::update_viewport()
{
    ViewportItem::update_viewport();
    update_data_range();
}

//! Returns Data2DItem if exists.

Data2DItem* ColorMapViewportItem::data_item() const
{
    auto colormap_item = item<ColorMapItem>(T_ITEMS);
    return colormap_item ? colormap_item->dataItem() : nullptr;
}

//! Returns range of x-axis as defined in underlying Data2DItem.

std::pair<double, double> ColorMapViewportItem::data_xaxis_range() const
{
    auto dataItem = data_item();
    return dataItem && dataItem->xAxis() ? dataItem->xAxis()->range() : default_axis_range;
}

//! Returns range of y-axis as defined in underlying Data2DItem.

std::pair<double, double> ColorMapViewportItem::data_yaxis_range() const
{
    auto dataItem = data_item();
    return dataItem && dataItem->yAxis() ? dataItem->yAxis()->range() : default_axis_range;
}

//! Updates zAxis to lower, upper values over all data points.

void ColorMapViewportItem::update_data_range()
{
    if (auto dataItem = data_item(); dataItem) {
        auto values = dataItem->content();
        auto [lower, upper] = std::minmax_element(std::begin(values), std::end(values));
        colorAxis()->set_range(*lower, *upper);
    }
}
