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
#include "externalproperty.h"
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

//! Returns default property representing non-existent material.

ExternalProperty MaterialModel::undefined_material()
{
    return ExternalProperty("Undefined", QColor(Qt::red));
}

//! Returns vector of properties representing possible choice of materials.

std::vector<ExternalProperty> MaterialModel::material_data()
{
    std::vector<ExternalProperty> result;

    result.push_back(undefined_material());
    for (auto container : rootItem()->children()) {
        for (auto item : container->children()) {
            if (auto material = dynamic_cast<SLDMaterialItem*>(item)) {
                auto text = material->getItemValue(SLDMaterialItem::P_NAME).value<std::string>();
                auto color = material->getItemValue(SLDMaterialItem::P_COLOR).value<QColor>();
                auto id = material->identifier();
                result.push_back(ExternalProperty(text, color, id));
            }
        }
    }
    return result;
}


//! Populates the model with some default content.

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
