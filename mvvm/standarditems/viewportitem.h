// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWPORTITEM_H
#define MVVM_VIEWPORTITEM_H

#include "compounditem.h"

namespace ModelView
{

class GraphItem;
class ViewportAxisItem;

/*!
@class ViewportItem
@brief Base class to represent 2D viewport.

Used to define x,y axis for graphs and 2d colormaps, intended for use in QCustomPlot context.
*/

class CORE_EXPORT ViewportItem : public CompoundItem
{
public:
    static inline const std::string P_XAXIS = "P_XAXIS";
    static inline const std::string P_YAXIS = "P_YAXIS";
    ViewportItem(const model_type& model);

    ViewportAxisItem* xAxis() const;

    ViewportAxisItem* yAxis() const;

protected:
    void register_xy_axes();
};

} // namespace ModelView

#endif // MVVM_VIEWPORTITEM_H
