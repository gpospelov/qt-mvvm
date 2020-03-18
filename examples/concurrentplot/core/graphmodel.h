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

//! Main application model holding data for single graph.
//! Contains few Data1DItem's, GraphItem's and ViewPortItem.

class GraphModel : public ModelView::SessionModel
{
public:
    GraphModel();

    void set_data(const std::vector<double>& data);

private:
    void init_model();
    void add_graph(ModelView::ContainerItem* container, ModelView::GraphViewportItem* viewport);
};

#endif // GRAPHMODEL_H
