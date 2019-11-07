// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
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
