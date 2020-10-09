// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/factories/itemcataloguefactory.h>
#include <mvvm/model/compounditem.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/colormapitem.h>
#include <mvvm/standarditems/colormapviewportitem.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/data2ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/standarditems/linkeditem.h>
#include <mvvm/standarditems/plottableitems.h>
#include <mvvm/standarditems/vectoritem.h>

using namespace ModelView;

std::unique_ptr<ItemCatalogue> ModelView::CreateStandardItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<ColorMapItem>();
    result->registerItem<ColorMapViewportItem>();
    result->registerItem<CompoundItem>();
    result->registerItem<ContainerItem>();
    result->registerItem<Data1DItem>();
    result->registerItem<Data2DItem>();
    result->registerItem<FixedBinAxisItem>();
    result->registerItem<GraphItem>();
    result->registerItem<GraphViewportItem>();
    result->registerItem<LinkedItem>();
    result->registerItem<PointwiseAxisItem>();
    result->registerItem<PropertyItem>();
    result->registerItem<SessionItem>();
    result->registerItem<TextItem>();
    result->registerItem<VectorItem>();
    result->registerItem<ViewportAxisItem>();
    return result;
}
