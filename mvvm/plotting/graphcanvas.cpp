// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphcanvas.h"
#include "qcustomplot.h"
#include "axisplotcontrollers.h"
#include "graphviewportitem.h"
#include "axisitems.h"
#include "graphitemcontroller.h"
#include "graphitem.h"
#include <QBoxLayout>

using namespace ModelView;

struct GraphCanvas::GraphCanvasPrivate {
    QCustomPlot* m_customPlot{nullptr};
    std::unique_ptr<AxisPlotController> m_xAxisController;
    std::unique_ptr<AxisPlotController> m_yAxisController;
    std::unique_ptr<GraphItemController> m_graphController;

    GraphCanvasPrivate() : m_customPlot(new QCustomPlot)
    {
        m_xAxisController = std::make_unique<XAxisPlotController>(m_customPlot);
        m_yAxisController = std::make_unique<YAxisPlotController>(m_customPlot);
        m_graphController = std::make_unique<GraphItemController>(m_customPlot);
    }

    QCustomPlot* customPlot()
    {
        return m_customPlot;
    }
};

GraphCanvas::GraphCanvas(QWidget* parent)
    : QWidget(parent), p_impl(std::make_unique<GraphCanvasPrivate>())
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(p_impl->m_customPlot);
    setLayout(layout);

    setMouseTracking(true);
    p_impl->customPlot()->setMouseTracking(true);
    p_impl->customPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_impl->customPlot()->axisRect()->setupFullAxesBox(true);
}

void GraphCanvas::setItem(GraphViewportItem* viewport_item)
{
    p_impl->m_xAxisController->setItem(&viewport_item->item<ViewportAxisItem>(GraphViewportItem::P_XAXIS));
    p_impl->m_yAxisController->setItem(&viewport_item->item<ViewportAxisItem>(GraphViewportItem::P_YAXIS));
    p_impl->m_graphController->setItem(&viewport_item->item<GraphItem>(GraphViewportItem::T_GRAPHS));
}

GraphCanvas::~GraphCanvas() = default;
