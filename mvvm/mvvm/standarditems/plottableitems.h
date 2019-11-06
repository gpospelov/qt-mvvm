// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PLOTTABLEITEMS_H
#define MVVM_PLOTTABLEITEMS_H

//! @file plottableitems.h
//! Collection of items to plot in QCustomPlot context.

#include <mvvm/model/compounditem.h>

namespace ModelView
{

/*!
@class TextItem
@brief Represent text item on plot.
*/

class CORE_EXPORT TextItem : public CompoundItem
{
public:
    static inline const std::string P_TEXT = "P_TEXT";
    static inline const std::string P_FONT = "P_FONT";
    static inline const std::string P_SIZE = "P_SIZE";
    TextItem();
};

} // namespace ModelView

#endif // MVVM_PLOTTABLEITEMS_H
