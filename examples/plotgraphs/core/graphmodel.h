// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <mvvm/model/sessionmodel.h>

namespace ModelView {
class GraphViewportItem;
class ContainerItem;
}

/*!
@class GraphModel
@brief Main application model to demonstrate how to plot data.

Contains few Data1DItem's, GraphItem's and ViewPortItem. Provides functionality to easily
add and remove graphs.
*/

class GraphModel : public ModelView::SessionModel
{
public:
    GraphModel();

    void add_graph();

    void remove_graph();

    void randomize_graphs();


private:
    ModelView::GraphViewportItem* viewport();
    ModelView::ContainerItem* data_container();

    void init_model();
};

#endif // GRAPHMODEL_H
