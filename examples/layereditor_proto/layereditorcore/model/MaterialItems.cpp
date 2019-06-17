// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialItems.h"
#include "item_constants.h"
#include "vectoritem.h"
#include <QColor>

using namespace ModelView;

// ----------------------------------------------------------------------------

MaterialContainerItem::MaterialContainerItem()
    : ModelView::CompoundItem(::Constants::MaterialContainerType)
{
    registerTag(TagInfo::universalTag("materials", {::Constants::SLDMaterialType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

const std::string MaterialBaseItem::P_NAME = "P_NAME";
const std::string MaterialBaseItem::P_COLOR = "P_COLOR";

MaterialBaseItem::MaterialBaseItem(const std::string& model_type)
    : ModelView::CompoundItem(model_type)
{
}

void MaterialBaseItem::register_name()
{
    addProperty<>(P_NAME, "Unnamed")->setDisplayName("Name");
}

void MaterialBaseItem::register_color()
{
    addProperty<>(P_COLOR, QColor(Qt::green))->setDisplayName("Color");
}

// ----------------------------------------------------------------------------

const std::string SLDMaterialItem::P_SLD_REAL = "P_SLD_REAL";
const std::string SLDMaterialItem::P_SLD_IMAG = "P_SLD_IMAG";

SLDMaterialItem::SLDMaterialItem() : MaterialBaseItem(::Constants::SLDMaterialType)
{
    register_name();
    register_color();
    addProperty<>(P_SLD_REAL, 1e-06)->setDisplayName("SLD, real");
    addProperty<>(P_SLD_IMAG, 1e-08)->setDisplayName("SLD, imag");
    addProperty<VectorItem>("Magnetization");
}

void SLDMaterialItem::set_properties(const std::string& name, const QColor& color, double real,
                                     double imag)
{
    setItemValue(P_NAME, QVariant::fromValue(name));
    setItemValue(P_COLOR, QVariant::fromValue(color));
    setItemValue(P_SLD_REAL, real);
    setItemValue(P_SLD_IMAG, imag);
}
