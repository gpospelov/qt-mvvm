// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "jobmodel.h"
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

JobModel::JobModel() : SessionModel("MaterialModel")
{
    init_model();
}

void JobModel::init_model()
{
    auto viewport = insertItem<GraphViewportItem>();
    auto data = insertItem<Data1DItem>();
    auto graph = insertItem<GraphItem>(viewport);
    graph->setDataItem(data);
}
