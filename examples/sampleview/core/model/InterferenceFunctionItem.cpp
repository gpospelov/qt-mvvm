// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "InterferenceFunctionItem.h"
#include "item_constants.h"

const std::string InterferenceFunctionItem::P_POSITION_VARIANCE = "PositionVariance";

InterferenceFunctionItem::InterferenceFunctionItem()
    : LocatedItem(::Constants::InterferenceFunctionType)
{
    addProperty(P_POSITION_VARIANCE, 0.0);
}
