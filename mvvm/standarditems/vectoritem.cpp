// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "vectoritem.h"

using namespace ModelView;

const std::string VectorItem::P_X = "X";
const std::string VectorItem::P_Y = "Y";
const std::string VectorItem::P_Z = "Z";

VectorItem::VectorItem() : CompoundItem(Constants::VectorType)
{
    addProperty<ModelView::PropertyItem>(P_X, 0.0);
    addProperty<ModelView::PropertyItem>(P_Y, 0.0);
    addProperty<ModelView::PropertyItem>(P_Z, 0.0);
}
