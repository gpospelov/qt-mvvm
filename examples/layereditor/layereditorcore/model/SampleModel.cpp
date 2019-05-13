// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SampleModel.h"
#include "ItemCatalogue.h"
#include "itemmanager.h"
#include "itemfactory.h"
#include "item_constants.h"

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    m_item_manager->setItemFactory(
        std::make_unique<ModelView::ItemFactory>(CreateItemCatalogue()));

    auto multilayer = insertNewItem(Constants::MultiLayerType);
    auto layer = insertNewItem(Constants::LayerType, multilayer);

    auto assembly = insertNewItem(Constants::MultiLayerType, multilayer);
    layer = insertNewItem(Constants::LayerType, assembly);
    layer = insertNewItem(Constants::LayerType, assembly);

    layer = insertNewItem(Constants::LayerType, multilayer);
}
