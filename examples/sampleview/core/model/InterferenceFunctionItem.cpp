// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
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
