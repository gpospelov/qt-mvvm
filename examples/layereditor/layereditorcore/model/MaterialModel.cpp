// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialModel.h"
#include "MaterialItems.h"
#include "item_constants.h"
#include "itemcatalogue.h"
#include <QColor>

using namespace ModelView;

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<MaterialContainerItem>();
    result->registerItem<SLDMaterialItem>();
    return result;
}
} // namespace

MaterialModel::MaterialModel() : SessionModel("MaterialModel")
{
    setItemCatalogue(CreateItemCatalogue());
    init_model();
}

//! Populated the model with some default content.

void MaterialModel::init_model()
{
    auto container = insertNewItem(::Constants::MaterialContainerType);
    auto material =
        dynamic_cast<SLDMaterialItem*>(insertNewItem(::Constants::SLDMaterialType, container));
    material->set_properties("Air", QColor(Qt::blue), 1e-06, 1e-07);

    material =
        dynamic_cast<SLDMaterialItem*>(insertNewItem(::Constants::SLDMaterialType, container));
    material->set_properties("Au", QColor(Qt::yellow), 2.4e-06, 5.6e-07);

    material =
        dynamic_cast<SLDMaterialItem*>(insertNewItem(::Constants::SLDMaterialType, container));
    material->set_properties("Si2O3", QColor(Qt::darkCyan), 3.4e-06, 3.6e-07);
}
