// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLORMAPVIEWPORTITEM_H
#define MVVM_COLORMAPVIEWPORTITEM_H

#include "viewportitem.h"

namespace ModelView
{

class GraphItem;
class ViewportAxisItem;

/*!
@class ColorMapViewportItem
@brief Container with viewport and collection of ColorMapItem's to plot.
*/

class CORE_EXPORT ColorMapViewportItem : public ViewportItem
{
public:
    static inline const std::string P_ZAXIS = "P_ZAXIS";
    ColorMapViewportItem();

    ViewportAxisItem* zAxis() const;

    void update_viewport() override;

private:
    virtual std::pair<double, double> data_xrange() const override;
    virtual std::pair<double, double> data_yrange() const override;
    void update_data_range();
};

} // namespace ModelView

#endif // MVVM_COLORMAPVIEWPORTITEM_H
