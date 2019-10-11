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
#include "externalproperty.h"
#include "item_constants.h"
#include "itemcatalogue.h"
#include "modelutils.h"
#include <QColor>

using namespace ModelView;

namespace
{
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<MaterialContainerItem>();
    result->registerItem<SLDMaterialItem>();
    result->registerItem<RefIndexMaterialItem>();
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

//! Returns vector of properties representing possible choice of materials for the given container.
//! Here we assume that all materials seats in top level material containers.
//! If no container_id was given, the very first container is examined.

std::vector<ExternalProperty> MaterialModel::material_data(std::string container_id) const
 {
    std::vector<ExternalProperty> result{undefined_material()};
    const auto containers = rootItem()->children();
    if (!containers.empty() && container_id.empty())
        container_id = Utils::TopItem<MaterialContainerItem>(this)->identifier();

    for (auto container : containers) {
        if (container->identifier() != container_id)
            continue;
        for (auto item : container->children()) {
            if (auto material = dynamic_cast<MaterialBaseItem*>(item)) {
                auto text = material->property(MaterialBaseItem::P_NAME).value<std::string>();
                auto color = material->property(MaterialBaseItem::P_COLOR).value<QColor>();
                auto id = material->identifier();
                result.push_back(ExternalProperty(text, color, id));
            }
        }
    }
    return result;
}

//! Returns property from given material id.

ExternalProperty MaterialModel::material_property(const std::string& id, std::string container_id)
{
    auto materials = material_data(container_id);
    for (const auto& prop : material_data())
        if (prop.identifier() == id)
            return prop;

    return undefined_material();
}

//! Populates the model with some default content.

void MaterialModel::init_model()
{
    auto container = insertNewItem(::Constants::MaterialContainerType);
    auto material = insertItem<SLDMaterialItem>(container, MaterialContainerItem::T_MATERIALS);
    material->set_properties("Air", QColor(Qt::blue), 1e-06, 1e-07);

    material = insertItem<SLDMaterialItem>(container, MaterialContainerItem::T_MATERIALS);
    material->set_properties("Au", QColor(Qt::yellow), 2.4e-06, 5.6e-07);

    material = insertItem<SLDMaterialItem>(container, MaterialContainerItem::T_MATERIALS);
    material->set_properties("Si2O3", QColor(Qt::darkCyan), 3.4e-06, 3.6e-07);
}
