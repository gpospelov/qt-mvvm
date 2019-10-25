// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "standarditemcatalogue.h"
#include "mvvm_types.h"
#include "vectoritem.h"
#include "propertyitem.h"
#include "compounditem.h"
#include "linkeditem.h"
#include "axisitems.h"
#include "data1ditem.h"
#include "data2ditem.h"
#include "graphitem.h"
#include "graphviewportitem.h"
#include "plottableitems.h"
#include "containeritem.h"
#include "colormapitem.h"
#include "colormapviewportitem.h"

using namespace ModelView;

std::unique_ptr<ItemCatalogue> ModelView::CreateStandardItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<SessionItem>();
    result->registerItem<PropertyItem>();
    result->registerItem<CompoundItem>();
    result->registerItem<VectorItem>();
    result->registerItem<LinkedItem>();
    result->registerItem<FixedBinAxisItem>();
    result->registerItem<ViewportAxisItem>();
    result->registerItem<AmplitudeAxisItem>();
    result->registerItem<Data1DItem>();
    result->registerItem<Data2DItem>();
    result->registerItem<GraphItem>();
    result->registerItem<GraphViewportItem>();
    result->registerItem<ColorMapItem>();
    result->registerItem<ColorMapViewportItem>();
    result->registerItem<TextItem>();
    result->registerItem<ContainerItem>();
    return result;
}
