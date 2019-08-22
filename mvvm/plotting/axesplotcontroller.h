// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_AXESPLOTCONTROLLER_H
#define MVVM_AXESPLOTCONTROLLER_H


#include "itemcontroller.h"

class QCustomPlot;

namespace ModelView
{

class GraphViewportItem;

/*!
@class AxesPlotController
@brief Establish communication between QCustomPlot and GraphViewportItem related to
viewport's x/y axes.
*/

class CORE_EXPORT AxesPlotController : public ItemController
{
public:
    explicit AxesPlotController(QCustomPlot* plot, QObject* parent = nullptr);
    ~AxesPlotController() override;

private:
    struct AxesPlotControllerPrivate;
    std::unique_ptr<AxesPlotControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_AXESPLOTCONTROLLER_H
