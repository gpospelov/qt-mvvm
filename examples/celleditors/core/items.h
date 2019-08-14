// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMS_H
#define ITEMS_H

/*!
@file items.h
@brief Collection of items for our application model.
*/

#include "compounditem.h"
#include <string>

/*!
@class DemoPropertiesItem
@brief Demo item which demonstrates all supported properties.
*/

class DemoPropertiesItem : public ModelView::CompoundItem
{
public:
    static const std::string P_BOOL_PROPERTY;
    static const std::string P_INTEGER_PROPERTY;
    static const std::string P_STRING_PROPERTY;
    static const std::string P_DOUBLE_PROPERTY;
    static const std::string P_COLOR_PROPERTY;
    static const std::string P_COMBO_PROPERTY;
    static const std::string P_EXTERNAL_PROPERTY;

    DemoPropertiesItem();
};

#endif // ITEMS_H
