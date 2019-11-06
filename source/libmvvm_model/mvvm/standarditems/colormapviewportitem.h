// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H
#define MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H

#include <mvvm/standarditems/viewportitem.h>

namespace ModelView
{

class Data2DItem;

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
    Data2DItem* data_item() const;
    virtual std::pair<double, double> data_xaxis_range() const override;
    virtual std::pair<double, double> data_yaxis_range() const override;
    void update_data_range();
};

} // namespace ModelView

#endif  // MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H
