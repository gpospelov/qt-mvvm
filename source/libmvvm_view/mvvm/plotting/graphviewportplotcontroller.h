// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H
#define MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCustomPlot;

namespace ModelView {

class GraphViewportItem;

//! Establishes communications and mutual updates for GraphViewportItem and QCutomPlot.
//! Populates custom plot with all graphs found in GraphViewportItem.

class MVVM_VIEW_EXPORT GraphViewportPlotController : public ItemListener<GraphViewportItem> {
public:
    explicit GraphViewportPlotController(QCustomPlot* plot);
    ~GraphViewportPlotController() override;

protected:
    void subscribe() override;

private:
    struct GraphViewportPlotControllerImpl;
    std::unique_ptr<GraphViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H
