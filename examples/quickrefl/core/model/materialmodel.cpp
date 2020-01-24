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

//! Clones material and adds it at the bottom of MaterialContainerItem.

void MaterialModel::cloneMaterial(const MaterialBaseItem* item)
{
    SessionModel::copyItem(item, materialContainer());
}

//! Adds default material.

void MaterialModel::addDefaultMaterial()
{
    auto material = insertItem<SLDMaterialItem>(materialContainer());
    material->set_properties("Default", QColor(Qt::green), 1e-03, 1e-05);
}

//! Populates the model with some default content.

void MaterialModel::init_model()
{
    auto container = insertItem<MaterialContainerItem>();
    auto material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Air", QColor(Qt::blue), 1e-06, 1e-07);

    material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Au", QColor(Qt::yellow), 2.4e-06, 5.6e-07);

    material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Si2O3", QColor(Qt::darkCyan), 3.4e-06, 3.6e-07);
}

MaterialContainerItem* MaterialModel::materialContainer()
{
    return Utils::TopItem<MaterialContainerItem>(const_cast<MaterialModel*>(this));
}
