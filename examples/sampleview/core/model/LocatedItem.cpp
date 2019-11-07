// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "LocatedItem.h"

using namespace ModelView;

LocatedItem::LocatedItem(const std::string& model_type)
    : CompoundItem(model_type)
{
    addProperty(P_X_POS, 0.0)->setDisplayName("x");
    addProperty(P_Y_POS, 0.0)->setDisplayName("y");
}
