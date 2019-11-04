// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLORMAPVIEWPORTPLOTCONTROLLER_H
#define MVVM_COLORMAPVIEWPORTPLOTCONTROLLER_H

#include "itemcontroller.h"

class QCustomPlot;

namespace ModelView
{

class ColorMapViewportItem;

/*!
@class ColorMapViewportPlotController
@brief Establishes communications and mutual updates for ColorMapViewportItem and QCutomPlot.

Populates custom plot with color map and tracks updates in items.
*/

class CORE_EXPORT ColorMapViewportPlotController : public ItemController<ColorMapViewportItem>
{
public:
    explicit ColorMapViewportPlotController(QCustomPlot* plot);
    ~ColorMapViewportPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapViewportPlotControllerImpl;
    std::unique_ptr<ColorMapViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COLORMAPVIEWPORTPLOTCONTROLLER_H
