// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLORMAPITEM_H
#define MVVM_COLORMAPITEM_H

#include "compounditem.h"

namespace ModelView
{

class Data2DItem;

/*!
@class ColorMapItem
@brief Two-dimensional color map representation of Data2DItem.

Contains plot properties (i.e. color, gradient etc) and link to Data2DItem, which will provide
actual data to plot. ColorMapItem is intended for plotting only via ColorMapViewportItem.
*/

class CORE_EXPORT ColorMapItem : public CompoundItem
{
public:
    static inline const std::string P_LINK = "P_LINK";
    static inline const std::string P_TITLE = "P_TITLE";
    static inline const std::string P_GRADIENT = "P_GRADIENT";
    static inline const std::string P_INTERPOLATION = "P_INTERPOLATION";
    ColorMapItem();

    void setDataItem(const Data2DItem* item);

    Data2DItem* dataItem() const;
};

} // namespace ModelView

#endif // MVVM_COLORMAPITEM_H
