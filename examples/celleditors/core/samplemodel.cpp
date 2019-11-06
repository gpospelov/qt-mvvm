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

namespace  {
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<DemoPropertiesItem>();
    return result;
}
}


SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
}
