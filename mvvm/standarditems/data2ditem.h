// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DATA2DITEM_H
#define MVVM_DATA2DITEM_H

#include "compounditem.h"
#include <vector>

namespace ModelView
{

/*!
@class Data2DItem
@brief Represents two-dimensional data (axes definition and 2d array of values).

Values are stored in Data2DItem itself, axes is attached as a child. Corresponding plot
properties will be served by ColorMapItem.
*/

class CORE_EXPORT Data2DItem : public CompoundItem
{
public:
    static inline const std::string T_XAXIS = "T_XAXIS";
    static inline const std::string T_YAXIS = "T_YAXIS";
    Data2DItem();
};

} // namespace ModelView

#endif // MVVM_DATA2DITEM_H
