// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphitemcontroller.h"
#include "graphitem.h"
#include "itemmapper.h"
#include "qcustomplot.h"
#include <QVector>

using namespace ModelView;

struct GraphItemController::GraphItemControllerPrivate {

    GraphItemController* m_controller{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    bool m_block_update{false};
    QCPGraph* m_graph{nullptr};

    GraphItemControllerPrivate(GraphItemController* controller, QCustomPlot* plot)
        : m_controller(controller), m_customPlot(plot)
    {
    }

    void setGraphFromItem()
    {
        assert(m_graph == nullptr);

        auto graph_item = m_controller->currentItem();

        auto graph = m_customPlot->addGraph();
        graph->setData(QVector<double>::fromStdVector(graph_item->binCenters()),
                       QVector<double>::fromStdVector(graph_item->binValues()));
    }
};

GraphItemController::GraphItemController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphItemControllerPrivate>(this, custom_plot))
{
}

void GraphItemController::subscribe()
{
    p_impl->setGraphFromItem();
}

GraphItemController::~GraphItemController() = default;
