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
#include "item_constants.h"

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue()
{
    std::unique_ptr<ModelView::ItemCatalogue> result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<DemoItem>();
    result->registerItem<DemoContainerItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
    init_model_content();
}

//! Generates initial model content.

void SampleModel::init_model_content()
{
    auto container = insertNewItem(Constants::DemoContainerItemType);
    insertNewItem(Constants::DemoItemType, container);
    insertNewItem(Constants::DemoItemType, container);

    container = insertNewItem(Constants::DemoContainerItemType);
    insertNewItem(Constants::DemoItemType, container);
    insertNewItem(Constants::DemoItemType, container);
    insertNewItem(Constants::DemoItemType, container);
}
