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

ColorMapViewportItem::ColorMapViewportItem() : CompoundItem(Constants::ColorMapViewportItemType)
{
    addProperty<ViewportAxisItem>(P_XAXIS)->setDisplayName("X axis");
    addProperty<ViewportAxisItem>(P_YAXIS)->setDisplayName("Y axis");
    registerTag(TagInfo::universalTag(T_COLORMAP, {Constants::ColorMapItemType}),
                /*set_default*/ true);
}

ViewportAxisItem* ColorMapViewportItem::xAxis() const
{
    return item<ViewportAxisItem>(P_XAXIS);
}

ViewportAxisItem* ColorMapViewportItem::yAxis() const
{
    return item<ViewportAxisItem>(P_YAXIS);
}
