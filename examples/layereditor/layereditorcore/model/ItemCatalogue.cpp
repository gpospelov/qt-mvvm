// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "ItemCatalogue.h"
#include "standarditemcatalogue.h"
#include "MultiLayerItem.h"
#include "LayerItem.h"
#include "MaterialItems.h"

std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = ModelView::CreateStandardItemCatalogue();
    result->add<MultiLayerItem>();
    result->add<LayerItem>();
    result->add<MaterialContainerItem>();
    result->add<SLDMaterialItem>();
    return result;
}
