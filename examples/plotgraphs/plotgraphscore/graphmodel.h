// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PLOTGRAPHSCORE_GRAPHMODEL_H
#define PLOTGRAPHSCORE_GRAPHMODEL_H

#include "mvvm/model/sessionmodel.h"

namespace ModelView {
class GraphViewportItem;
class ContainerItem;
} // namespace ModelView

namespace PlotGraphs {

//! Main application model to demonstrate how to plot data.
//! Contains few Data1DItem's, GraphItem's and ViewPortItem. Provides functionality to easily
//! add and remove graphs.

class GraphModel : public ModelView::SessionModel {
public:
    GraphModel();

    void addGraph();

    void removeGraph();

    void randomizeGraphs();

    void undo();

    void redo();

private:
    ModelView::GraphViewportItem* viewport();
    ModelView::ContainerItem* dataContainer();

    void populateModel();
};

} // namespace PlotGraphs

#endif // PLOTGRAPHSCORE_GRAPHMODEL_H
