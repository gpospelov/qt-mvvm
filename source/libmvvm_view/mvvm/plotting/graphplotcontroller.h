// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHPLOTCONTROLLER_H
#define MVVM_PLOTTING_GRAPHPLOTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCustomPlot;

namespace ModelView {

class GraphItem;

//! Establish communication between QCPGraph and GraphItem.
//! Provides update on QCPGraph (data points, line style, color, etc) when GraphItem is changed.
//! QCPGraph is added to QCustomPlot plottables, when controller is created, and removed from
//! plottables when controller is destroyed.

class MVVM_VIEW_EXPORT GraphPlotController : public ItemListener<GraphItem> {
public:
    explicit GraphPlotController(QCustomPlot* plot);
    ~GraphPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct GraphItemControllerImpl;
    std::unique_ptr<GraphItemControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHPLOTCONTROLLER_H
