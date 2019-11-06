// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H
#define MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H

#include <mvvm/signals/itemcontroller.h>
#include <memory>

class QCustomPlot;
class QCPColorScale;

namespace ModelView
{

class ColorMapItem;

/*!
@class ColorMapPlotController
@brief Establish communication between QCPColorMap and ColorMapItem.

Provide update on QCPColorMap when ColorMapItem is changed. QCPColorMap is added to
QCustomPlot plottables, when controller is created, and removed from plottables, when controller
is destroyed.
*/

class CORE_EXPORT ColorMapPlotController : public ItemController<ColorMapItem>
{
public:
    explicit ColorMapPlotController(QCustomPlot* plot, QCPColorScale* color_scale=nullptr);
    ~ColorMapPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapPlotControllerImpl;
    std::unique_ptr<ColorMapPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H
