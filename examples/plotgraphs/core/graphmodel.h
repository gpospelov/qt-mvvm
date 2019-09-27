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

#include "sessionmodel.h"

namespace ModelView {
class GraphViewportItem;
}

/*!
@class GraphModel
@brief Main application model.

Contains few Data1DItem's, GraphItem's and ViewPortItem.
*/

class GraphModel : public ModelView::SessionModel
{
public:
    GraphModel();

    void add_graph();

    void update_graphs();

private:
    ModelView::GraphViewportItem* viewport();
    void init_model();
};

#endif // GRAPHMODEL_H
