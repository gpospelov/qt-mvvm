// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <layereditor/model/item_constants.h>
#include <layereditor/model/materialitems.h>
#include <mvvm/standarditems/vectoritem.h>

using namespace ModelView;

MaterialContainerItem::MaterialContainerItem()
    : ModelView::CompoundItem(::Constants::MaterialContainerType)
{
    registerTag(TagInfo::universalTag("materials", {::Constants::SLDMaterialType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

MaterialBaseItem::MaterialBaseItem(const std::string& model_type)
    : ModelView::CompoundItem(model_type)
{
}

void MaterialBaseItem::register_name()
{
    addProperty(P_NAME, "Unnamed")->setDisplayName("Name");
}

void MaterialBaseItem::register_color()
{
    addProperty(P_COLOR, QColor(Qt::green))->setDisplayName("Color");
}

// ----------------------------------------------------------------------------

SLDMaterialItem::SLDMaterialItem() : MaterialBaseItem(::Constants::SLDMaterialType)
{
    register_name();
    register_color();
    addProperty(P_SLD_REAL, 1e-06)->setDisplayName("SLD, real");
    addProperty(P_SLD_IMAG, 1e-08)->setDisplayName("SLD, imag");
    addProperty<VectorItem>("Magnetization");
}

void SLDMaterialItem::set_properties(const std::string& name, const QColor& color, double real,
                                     double imag)
{
    setProperty(P_NAME, name);
    setProperty(P_COLOR, color);
    setProperty(P_SLD_REAL, real);
    setProperty(P_SLD_IMAG, imag);
}
