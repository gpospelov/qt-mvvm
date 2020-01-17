// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ViewItemsModel.h"
#include <QColor>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>

using namespace ModelView;

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    // result->registerItem<MaterialContainerItem>();
    // result->registerItem<SLDMaterialItem>();
    return result;
}
} // namespace

ViewItemsModel::ViewItemsModel() : SessionModel("MaterialModel")
{
    setItemCatalogue(CreateItemCatalogue());
}


