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


MaterialBaseItem::MaterialBaseItem(const std::string& model_type)
    : ModelView::CompoundItem(model_type) {}


const std::string SLDMaterialItem::P_SLD_REAL = "P_SLD_REAL";
const std::string SLDMaterialItem::P_SLD_IMAG = "P_SLD_IMAG";

SLDMaterialItem::SLDMaterialItem()
    : MaterialBaseItem(Constants::SLDMaterialType)
{
    addProperty<ModelView::PropertyItem>(P_SLD_REAL, 1e-06);
    addProperty<ModelView::PropertyItem>(P_SLD_IMAG, 1e-08);
}
