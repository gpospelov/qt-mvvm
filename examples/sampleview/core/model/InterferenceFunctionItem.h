// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //
#ifndef INTERFERENCEFUNCTIONITEM_H
#define INTERFERENCEFUNCTIONITEM_H

#include "LocatedItem.h"

//! Base class for different (future) types of interference.
class InterferenceFunctionItem : public LocatedItem
{
public:
    static const std::string P_POSITION_VARIANCE;

    InterferenceFunctionItem();
};

#endif // INTERFERENCEFUNCTIONITEM_H
