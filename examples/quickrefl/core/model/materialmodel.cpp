// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialmodel.h"
#include "item_constants.h"
#include "materialitems.h"
#include <QColor>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/utils/numericutils.h>

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

const double rho_si = 2.01e-05;
const double mu_si = 5.96e-07;

const double rho_default = 9.4245e-06;
const double mu_default = 0.0;

const std::string air_material_name = "Air";
const std::string substrate_material_name = "Si";
const std::string default_material_name = "Default";

QColor random_color()
{
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    return QColor(rndm(), rndm(), rndm());
}

//! Returns map of good looking colors for standard material names.

std::map<std::string, QColor> name_to_color_map()
{
    std::map<std::string, QColor> result = {{air_material_name, QColor(179, 242, 255)},
                                            {substrate_material_name, QColor(205, 102, 0)},
                                            {default_material_name, QColor(Qt::green)}};
    return result;
}

QColor suggestMaterialColor(const std::string& name)
{
    static auto color_map = name_to_color_map();
    auto it = color_map.find(name);
    return it != color_map.end() ? it->second : random_color();
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
    std::vector<ExternalProperty> result;
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

//! Clones material and adds it at the bottom of MaterialContainerItem.

MaterialBaseItem* MaterialModel::cloneMaterial(const MaterialBaseItem* item)
{
    auto tagrow = item->parent()->tagRowOfItem(item).next();
    return static_cast<MaterialBaseItem*>(SessionModel::copyItem(item, item->parent(), tagrow));
}

//! Adds default material.

SLDMaterialItem* MaterialModel::addDefaultMaterial(const ModelView::TagRow& tagrow)
{
    auto material = insertItem<SLDMaterialItem>(materialContainer(), tagrow);
    material->set_properties("Default", QColor(Qt::green), rho_default, mu_default);
    return material;
}

//! Populates the model with some default content.

void MaterialModel::init_model()
{
    auto container = insertItem<MaterialContainerItem>();
    auto material = insertItem<SLDMaterialItem>(container);
    material->set_properties(air_material_name, suggestMaterialColor(air_material_name), 0.0, 0.0);
    material = insertItem<SLDMaterialItem>(container);
    material->set_properties(default_material_name, suggestMaterialColor(default_material_name),
                             rho_default, mu_default);
    material = insertItem<SLDMaterialItem>(container);
    material->set_properties(substrate_material_name, suggestMaterialColor(substrate_material_name),
                             rho_si, mu_si);
}

MaterialContainerItem* MaterialModel::materialContainer()
{
    return Utils::TopItem<MaterialContainerItem>(const_cast<MaterialModel*>(this));
}
