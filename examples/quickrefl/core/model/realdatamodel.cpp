// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "realdatamodel.h"
#include "datasetitem.h"
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

namespace
{

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<DataSetItem>();
    return result;
}

} // namespace

RealDataModel::RealDataModel() : SessionModel("RealDataModel")
{
    setItemCatalogue(CreateItemCatalogue());
    auto dataset = insertItem<DataSetItem>();

    // FIXME Fake data, remove at some point all below
    {
        auto data = insertItem<Data1DItem>(dataset->dataContainer());
        data->setAxis(PointwiseAxisItem::create(std::vector<double>{1.0, 2.0, 3.0}));
        data->setContent({10.0, 15.0, 30.0});

        auto viewport = insertItem<GraphViewportItem>(dataset->viewportContainer());
        auto graph = insertItem<GraphItem>(viewport);
        graph->setDataItem(data);
    }
}
