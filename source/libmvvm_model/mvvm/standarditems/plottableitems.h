// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_PLOTTABLEITEMS_H
#define MVVM_STANDARDITEMS_PLOTTABLEITEMS_H

//! @file plottableitems.h
//! Collection of items to plot in QCustomPlot context.

#include <mvvm/model/compounditem.h>

namespace ModelView
{

/*!
@class TextItem
@brief Represent text item on plot.
*/

class MVVM_MODEL_EXPORT TextItem : public CompoundItem
{
public:
    static inline const std::string P_TEXT = "P_TEXT";
    static inline const std::string P_FONT = "P_FONT";
    static inline const std::string P_SIZE = "P_SIZE";
    TextItem();
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_PLOTTABLEITEMS_H
