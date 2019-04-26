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

// ----------------------------------------------------------------------------

MaterialContainerItem::MaterialContainerItem()
    : ModelView::CompoundItem(Constants::MaterialContainerType)
{
    registerTag(ModelView::TagInfo::universalTag("materials", {Constants::SLDMaterialType}),
                /*set_as_default*/true);
}

// ----------------------------------------------------------------------------

const std::string MaterialBaseItem::P_NAME = "P_NAME";

MaterialBaseItem::MaterialBaseItem(const std::string& model_type)
    : ModelView::CompoundItem(model_type)
{

}

void MaterialBaseItem::register_name()
{
    addProperty<ModelView::PropertyItem>(P_NAME, "Unnamed")->setDisplayName("Name");
}

// ----------------------------------------------------------------------------

const std::string SLDMaterialItem::P_SLD_REAL = "P_SLD_REAL";
const std::string SLDMaterialItem::P_SLD_IMAG = "P_SLD_IMAG";

SLDMaterialItem::SLDMaterialItem()
    : MaterialBaseItem(Constants::SLDMaterialType)
{
    register_name();
    addProperty<ModelView::PropertyItem>(P_SLD_REAL, 1e-06)->setDisplayName("SLD, real");
    addProperty<ModelView::PropertyItem>(P_SLD_IMAG, 1e-08)->setDisplayName("SLD, imag");
}
