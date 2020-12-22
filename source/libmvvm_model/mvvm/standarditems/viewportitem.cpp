// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/viewportitem.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/axisitems.h"

using namespace ModelView;

ViewportItem::ViewportItem(const ModelView::model_type& model) : CompoundItem(model) {}

ViewportAxisItem* ViewportItem::xAxis() const
{
    return item<ViewportAxisItem>(P_XAXIS);
}

ViewportAxisItem* ViewportItem::yAxis() const
{
    return item<ViewportAxisItem>(P_YAXIS);
}

//! Sets range of x,y window to show all data.
//! Allows adding an additional margin to automatically calculated axis range. Margins are
//! given in relative units wrt calculated axis range.
//! Example: setViewportToContent(0.0, 0.1, 0.0, 0.1) will set axes to show all graphs with 10% gap
//! above and below graph's max and min.

void ViewportItem::setViewportToContent(double left, double top, double right, double bottom)
{
    Utils::BeginMacros(this, "setViewportToContent");
    auto [xmin, xmax] = data_xaxis_range();
    xAxis()->set_range(xmin - (xmax - xmin) * left, xmax + (xmax - xmin) * right);

    auto [ymin, ymax] = data_yaxis_range();
    yAxis()->set_range(ymin - (ymax - ymin) * bottom, ymax + (ymax - ymin) * top);
    Utils::EndMacros(this);
}

//! Sets range of x,y window to show all data.

void ViewportItem::setViewportToContent()
{
    Utils::BeginMacros(this, "setViewportToContent");
    auto [xmin, xmax] = data_xaxis_range();
    xAxis()->set_range(xmin, xmax);

    auto [ymin, ymax] = data_yaxis_range();
    yAxis()->set_range(ymin, ymax);
    Utils::EndMacros(this);
}

void ViewportItem::register_xy_axes()
{
    addProperty<ViewportAxisItem>(P_XAXIS)->setDisplayName("X axis");
    addProperty<ViewportAxisItem>(P_YAXIS)->setDisplayName("Y axis");
}
