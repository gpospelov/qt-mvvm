// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"
#include <mvvm/model/itemcatalogue.h>

using namespace ModelView;

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<BeamItem>();
    result->registerItem<DistributionNoneItem>();
    result->registerItem<DistributionGaussianItem>();
    result->registerItem<DistributionLogNormalItem>();
    result->registerItem<DistributionTrapezoidItem>();
    result->registerItem<DistributionGroupItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateItemCatalogue());
    init_model();
}

//! Provides initial model content.

void SampleModel::init_model()
{
    insertItem<BeamItem>();
    insertItem<DistributionGroupItem>();
}
