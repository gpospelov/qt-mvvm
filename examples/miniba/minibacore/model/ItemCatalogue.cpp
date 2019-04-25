// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "ItemCatalogue.h"
#include "defaultitemcatalogue.h"
#include "MultiLayerItem.h"
#include "LayerItem.h"
#include "MaterialItem.h"

std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = ModelView::CreateDefaultItemCatalogue();
    result->add<MultiLayerItem>();
    result->add<LayerItem>();
    result->add<MaterialItem>();
    return result;
}
