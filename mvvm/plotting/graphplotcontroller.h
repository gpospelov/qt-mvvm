// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_GRAPHPLOTCONTROLLER_H
#define MVVM_GRAPHPLOTCONTROLLER_H

#include "itemcontroller.h"

class QCustomPlot;

namespace ModelView
{

class GraphItem;

/*!
@class GraphPlotController
@brief Establish communication between QCPGraph and GraphItem.

Provide update on QCPGraph (data points, line style, color, etc) when GraphItem is changed.
QCPGraph is added to QCustomPlot plottables, when controller is created, and removed from
plottables when controller is destroyed.
*/

class CORE_EXPORT GraphPlotController : public ItemController<GraphItem>
{
public:
    explicit GraphPlotController(QCustomPlot* plot);
    ~GraphPlotController() override;

    GraphPlotController& operator=(const GraphPlotController& other) = delete;
    GraphPlotController(const GraphPlotController& other) = delete;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct GraphItemControllerPrivate;
    std::unique_ptr<GraphItemControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_GRAPHPLOTCONTROLLER_H
