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

using namespace ModelView;

struct GraphItemController::GraphItemControllerPrivate {

    GraphItemController* m_controller{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    bool m_block_update{false};

    GraphItemControllerPrivate(GraphItemController* controller, QCustomPlot* plot)
        : m_controller(controller), m_customPlot(plot)
    {
    }
};

GraphItemController::GraphItemController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<GraphItemControllerPrivate>(this, custom_plot))
{
}

void GraphItemController::subscribe()
{
}

QCustomPlot* GraphItemController::customPlot()
{
    return p_impl->m_customPlot;
}

GraphItemController::~GraphItemController() = default;
