// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <mvvm/model/sessionmodel.h>

namespace ModelView
{
class GraphViewportItem;
class ContainerItem;
} // namespace ModelView

namespace PlotGraphs
{

//! Main application model to demonstrate how to plot data.
//! Contains few Data1DItem's, GraphItem's and ViewPortItem. Provides functionality to easily
//! add and remove graphs.

class GraphModel : public ModelView::SessionModel
{
public:
    GraphModel();

    void add_graph();

    void remove_graph();

    void randomize_graphs();

    void undo();

    void redo();

private:
    ModelView::GraphViewportItem* viewport();
    ModelView::ContainerItem* data_container();

    void init_model();
};

} // namespace PlotGraphs

#endif // GRAPHMODEL_H
