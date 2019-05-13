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
#include "sessionitem.h"
#include <QColor>

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    std::unique_ptr<ModelView::ItemCatalogue> result = std::make_unique<ModelView::ItemCatalogue>();
    result->add<MaterialContainerItem>();
    result->add<SLDMaterialItem>();
    return result;
}
} // namespace

MaterialModel::MaterialModel() : SessionModel("MaterialModel")
{
    setItemCatalogue(CreateItemCatalogue());

    auto container = insertNewItem(Constants::MaterialContainerType);
    add_sld_material(container, "Air", QColor(Qt::blue), 1e-06, 1e-07);
    add_sld_material(container, "Au", QColor(Qt::yellow), 2.4e-06, 5.6e-07);
    add_sld_material(container, "Si2O3", QColor(Qt::darkCyan), 3.4e-06, 3.6e-07);
}

void MaterialModel::add_sld_material(ModelView::SessionItem* container, const std::string& name,
                                     const QColor& color, double real, double imag)
{
    auto material =
        dynamic_cast<SLDMaterialItem*>(insertNewItem(Constants::SLDMaterialType, container));
    material->setItemValue(MaterialBaseItem::P_NAME, QVariant::fromValue(name));
    material->setItemValue(MaterialBaseItem::P_COLOR, QVariant::fromValue(color));
    material->setItemValue(SLDMaterialItem::P_SLD_REAL, real);
    material->setItemValue(SLDMaterialItem::P_SLD_IMAG, imag);
}
