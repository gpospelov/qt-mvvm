// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphviewportitem.h"
#include "axisitems.h"

using namespace ModelView;

GraphViewportItem::GraphViewportItem() : CompoundItem(Constants::GraphViewportItemType)
{
    addProperty<ViewportAxisItem>(P_XAXIS)->setDisplayName("X axis");
    addProperty<ViewportAxisItem>(P_YAXIS)->setDisplayName("Y axis");
    registerTag(TagInfo::universalTag(T_GRAPHS, {Constants::GraphItemType}), /*set_default*/ true);
}
