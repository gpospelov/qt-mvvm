// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_AXISPLOTCONTROLLERS_H
#define MVVM_AXISPLOTCONTROLLERS_H

//! @file axisplotcontroller.h
//! Collection of controllers to connect QCustomPlot's axes with our AxisItems.

#include "itemcontroller.h"

class QCustomPlot;
class QCPAxis;

namespace ModelView
{

class ViewportAxisItem;

/*!
@class AxisPlotController
@brief Abstract base to establish communication between QCPAxis and ViewportAxisItem.

Provide mutual update of axis parameters (min, max, title) for two axes representations.
*/

class CORE_EXPORT AxisPlotController : public ItemController<ViewportAxisItem>
{
public:
    // FIXME make QCPAxis a constructor parameter and get rid from hierarchy here
    explicit AxisPlotController(QCustomPlot* plot);
    explicit AxisPlotController(QCPAxis* axis);

    ~AxisPlotController() override;

protected:
    virtual QCPAxis* customAxis();
    void subscribe() override;
    QCustomPlot* customPlot();

protected:
    struct AxesPlotControllerPrivate;
    std::unique_ptr<AxesPlotControllerPrivate> p_impl;
};

/*!
@class XAxisPlotController
@brief Establish communication between QCustomPlot->xAxis and ViewportAxisItem.
*/

class CORE_EXPORT XAxisPlotController : public AxisPlotController
{
public:
    explicit XAxisPlotController(QCustomPlot* cusom_plot);
    explicit XAxisPlotController(QCPAxis* axis);

protected:
    QCPAxis* customAxis() override;
};

/*!
@class YAxisPlotController
@brief Establish communication between QCustomPlot->yAxis and ViewportAxisItem.
*/

class CORE_EXPORT YAxisPlotController : public AxisPlotController
{
public:
    explicit YAxisPlotController(QCustomPlot* cusom_plot);
    explicit YAxisPlotController(QCPAxis* axis);

protected:
    QCPAxis* customAxis() override;
};

} // namespace ModelView

#endif // MVVM_AXISPLOTCONTROLLERS_H
