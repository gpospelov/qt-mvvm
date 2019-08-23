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
@brief Establish communication between QCPAxis and ViewportAxisItem.

Provide mutual update of axis parameters (min, max, title) for two axes representations.
*/

class CORE_EXPORT AxisPlotController : public ItemControllerV2<ViewportAxisItem>
{
public:
    explicit AxisPlotController(QCustomPlot* plot);
    ~AxisPlotController() override;

    void subscribe() override;

protected:
    virtual QCPAxis* customAxis() = 0;
    QCustomPlot* customPlot();

private:
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

protected:
    QCPAxis* customAxis() override;
};

} // namespace ModelView

#endif // MVVM_AXISPLOTCONTROLLERS_H
