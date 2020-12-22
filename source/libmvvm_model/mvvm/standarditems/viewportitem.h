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

#include "mvvm/model/compounditem.h"

namespace ModelView {

class ViewportAxisItem;

//! Base class to represent 2D viewport.
//! Contains x,y axis, indended to display graphs or 2d colormaps.

class MVVM_MODEL_EXPORT ViewportItem : public CompoundItem {
public:
    static inline const std::string P_XAXIS = "P_XAXIS";
    static inline const std::string P_YAXIS = "P_YAXIS";
    static inline const std::string T_ITEMS = "T_ITEMS";

    ViewportItem(const model_type& model);

    ViewportAxisItem* xAxis() const;

    ViewportAxisItem* yAxis() const;

    virtual void setViewportToContent(double left, double top, double right, double bottom);

    virtual void setViewportToContent();

protected:
    void register_xy_axes();

protected:
    virtual std::pair<double, double> data_xaxis_range() const = 0;
    virtual std::pair<double, double> data_yaxis_range() const = 0;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_VIEWPORTITEM_H
