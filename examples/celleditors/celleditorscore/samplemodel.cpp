// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "samplemodel.h"
#include "itemcatalogue.h"
#include "items.h"

namespace  {
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue()
{
    std::unique_ptr<ModelView::ItemCatalogue> result = std::make_unique<ModelView::ItemCatalogue>();
    result->add<DemoPropertiesItem>();
    return result;
}
}


SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
}
