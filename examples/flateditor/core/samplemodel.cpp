// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include <mvvm/model/itemcatalogue.h>
#include "items.h"

using namespace ModelView;

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<DistributionGaussianItem>();
    result->registerItem<DistributionLogNormalItem>();
    result->registerItem<DistributionTrapezoidItem>();
    result->registerItem<DistributionGroupItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
    init_model();
}

//! Provides initial model content.

void SampleModel::init_model()
{
    insertItem<DistributionGroupItem>();
}
