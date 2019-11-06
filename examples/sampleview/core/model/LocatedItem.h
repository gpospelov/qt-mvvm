// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LOCATEDITEM_H
#define LOCATEDITEM_H

/*!
@file LocatedItem.h
@brief Defines an item with 2D position information.
*/

#include <mvvm/model/compounditem.h>

/*!
@class LocatedItem
@brief Parent item for items represented in a graphics scene and containing (x, y) coordinates.
*/

class LocatedItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_X_POS = "P_X_POS";
    static inline const std::string P_Y_POS = "P_Y_POS";

    LocatedItem(const std::string& model_type);
};

#endif // LOCATEDITEM_H
