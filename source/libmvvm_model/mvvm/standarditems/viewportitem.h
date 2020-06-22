// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_VIEWPORTITEM_H
#define MVVM_STANDARDITEMS_VIEWPORTITEM_H

#include <mvvm/model/compounditem.h>

namespace ModelView
{

class ViewportAxisItem;

/*!
@class ViewportItem
@brief Base class to represent 2D viewport.

Used to define x,y axis for graphs and 2d colormaps, intended for use in QCustomPlot context.
*/

class MVVM_MODEL_EXPORT ViewportItem : public CompoundItem
{
public:
    static inline const std::string P_XAXIS = "P_XAXIS";
    static inline const std::string P_YAXIS = "P_YAXIS";
    static inline const std::string T_ITEMS = "T_ITEMS";
    ViewportItem(const model_type& model);

    ViewportAxisItem* xAxis() const;

    ViewportAxisItem* yAxis() const;

    virtual void update_viewport();

protected:
    void register_xy_axes();

private:
    virtual std::pair<double, double> data_xaxis_range() const = 0;
    virtual std::pair<double, double> data_yaxis_range() const = 0;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_VIEWPORTITEM_H
