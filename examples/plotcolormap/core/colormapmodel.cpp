// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapmodel.h"
#include "axisitems.h"
#include "containeritem.h"
#include "data2ditem.h"
#include "modelutils.h"
#include "colormapitem.h"
#include "colormapviewportitem.h"
#include <cmath>

using namespace ModelView;

namespace
{
// fills with data point
void fill_data(Data2DItem* data_item)
{
    const auto xAxis = data_item->xAxis();
    const auto yAxis = data_item->yAxis();
    std::vector<double> values;
    for (auto x : xAxis->binCenters()) {
        for (auto y : yAxis->binCenters()) {
            double r = 3.0 * std::sqrt(x * x + y * y) + 1e-2;
            double z = 2 * x * (std::cos(r + 2) / r - std::sin(r + 2) / r);
            values.push_back(z);
        }
    }

    data_item->setContent(values);
}
} // namespace

ColorMapModel::ColorMapModel() : SessionModel("ColorMapModel")
{
    init_model();
}

void ColorMapModel::add_colormap()
{
    auto data_item = insertItem<Data2DItem>(data_container());
    data_item->setAxes(FixedBinAxisItem::create(200, -5.0, 5.0),
                       FixedBinAxisItem::create(100, 0.0, 5.0));
    fill_data(data_item);

    auto viewport_item = insertItem<ColorMapViewportItem>();
    auto colormap_item = insertItem<ColorMapItem>(viewport_item);
    colormap_item->setDataItem(data_item);
}

ContainerItem* ColorMapModel::data_container()
{
    return Utils::TopItem<ContainerItem>(this);
}

void ColorMapModel::init_model()
{
    auto container = insertItem<ContainerItem>();
    container->setDisplayName("Data container");

    add_colormap();
}
