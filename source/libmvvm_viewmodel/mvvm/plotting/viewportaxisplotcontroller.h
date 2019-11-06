// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H
#define MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H

#include <mvvm/signals/itemcontroller.h>
#include <memory>

class QCPAxis;

namespace ModelView
{

class ViewportAxisItem;

/*!
@class ViewportAxisPlotController
@brief Establishes communication between QCPAxis and ViewportAxisItem.

Provide mutual update of axis parameters (min, max, title) for two axes representations.
*/

class CORE_EXPORT ViewportAxisPlotController : public ItemController<ViewportAxisItem>
{
public:
    explicit ViewportAxisPlotController(QCPAxis* axis);
    ~ViewportAxisPlotController() override;

protected:
    void subscribe() override;

public:
    struct AxesPlotControllerImpl;
    std::unique_ptr<AxesPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H
