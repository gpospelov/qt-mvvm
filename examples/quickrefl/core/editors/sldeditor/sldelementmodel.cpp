// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sldelementmodel.h"
#include "layerelementitem.h"

#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/reallimits.h>

using namespace ModelView;

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<LayerElementItem>();
    return result;
}

} // namespace

//! Contructor
SLDElementModel::SLDElementModel() : SessionModel("ViewItemsModel")
{
    setItemCatalogue(CreateItemCatalogue());
}

//! Add a layer item to the model and return its pointer
LayerElementItem* SLDElementModel::addLayer()
{
    auto layer_element_item = insertItem<LayerElementItem>();
    return layer_element_item;
}
