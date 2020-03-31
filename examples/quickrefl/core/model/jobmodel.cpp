// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "jobmodel.h"
#include "jobitem.h"
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

namespace
{

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<JobItem>();
    return result;
}

} // namespace

JobModel::JobModel() : SessionModel("JobModel")
{
    init_model();
}

Data1DItem* JobModel::sld_data() const
{
    return job_item()->sld_data();
}

GraphViewportItem* JobModel::sld_viewport() const
{
    return job_item()->sld_viewport();
}

Data1DItem* JobModel::specular_data() const
{
    return job_item()->specular_data();
}

GraphViewportItem* JobModel::specular_viewport() const
{
    return job_item()->specular_viewport();
}

JobItem* JobModel::job_item() const
{
    return Utils::TopItem<JobItem>(this);
}

void JobModel::init_model()
{
    setItemCatalogue(CreateItemCatalogue());
    insertItem<JobItem>();
}
