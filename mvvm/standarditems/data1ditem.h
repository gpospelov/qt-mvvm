// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DATA1DITEM_H
#define MVVM_DATA1DITEM_H

#include "compounditem.h"

namespace ModelView
{


/*!
@class Data1DItem
@brief Represents one-dimensional data (axis and values).

Values are stored in Data1DItem itself, axis is attached as a child.
*/

class CORE_EXPORT Data1DItem : public CompoundItem
{
public:
    static inline const std::string T_AXIS = "T_AXIS";
    Data1DItem();
};

} // namespace ModelView

#endif // MVVM_DATA1DITEM_H
