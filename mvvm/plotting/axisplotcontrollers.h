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
@brief Establishes communication between QCPAxis and ViewportAxisItem.

Provide mutual update of axis parameters (min, max, title) for two axes representations.
*/

class CORE_EXPORT AxisPlotController : public ItemController<ViewportAxisItem>
{
public:
    explicit AxisPlotController(QCPAxis* axis);
    ~AxisPlotController() override;

protected:
    void subscribe() override;

public:
    struct AxesPlotControllerPrivate;
    std::unique_ptr<AxesPlotControllerPrivate> p_impl;
};


} // namespace ModelView

#endif // MVVM_AXISPLOTCONTROLLERS_H
