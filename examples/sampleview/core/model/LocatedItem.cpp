// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LocatedItem.h"

using namespace ModelView;

const std::string LocatedItem::P_X_POS = "P_X_POS";
const std::string LocatedItem::P_Y_POS = "P_Y_POS";

LocatedItem::LocatedItem(const std::string& model_type)
    : CompoundItem(model_type)
{
    addProperty<>(P_X_POS, 0.0)->setDisplayName("x");
    addProperty<>(P_Y_POS, 0.0)->setDisplayName("y");
}

LocatedItem::~LocatedItem() = default;