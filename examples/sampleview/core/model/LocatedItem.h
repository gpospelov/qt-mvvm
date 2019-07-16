// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef LOCATEDITEM_H
#define LOCATEDITEM_H

/*!
@file LocatedItem.h
@brief Defines an item with 2D position information.
*/

#include "compounditem.h"

/*!
@class LocatedItem
@brief Parent item for items represented in a graphics scene and containing (x, y) coordinates.
*/

class LocatedItem : public ModelView::CompoundItem
{
public:
    static const std::string P_X_POS;
    static const std::string P_Y_POS;

    LocatedItem(const std::string& model_type);
    ~LocatedItem() override;
};

#endif // LOCATEDITEM_H