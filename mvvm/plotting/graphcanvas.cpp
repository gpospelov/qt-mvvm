// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphcanvas.h"
#include "graphviewportitem.h"
#include "graphviewportplotcontroller.h"
#include "qcustomplot.h"
#include "statuslabel.h"
#include "statusstringreporter.h"
#include "statusstringreporterfactory.h"
#include <QBoxLayout>

using namespace ModelView;

struct GraphCanvas::GraphCanvasImpl {
    QCustomPlot* custom_plot{nullptr};
    std::unique_ptr<GraphViewportPlotController> viewport_controller;
    std::unique_ptr<StatusStringReporter> reporter;
    StatusLabel* status_label{nullptr};

    GraphCanvasImpl() : custom_plot(new QCustomPlot), status_label(new StatusLabel)
    {
        viewport_controller = std::make_unique<GraphViewportPlotController>(custom_plot);

        auto on_mouse_move = [this](const std::string& str) {
            status_label->setText(QString::fromStdString(str));
        };
        reporter = CreateGraphReporter(custom_plot, on_mouse_move);
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

GraphCanvas::GraphCanvas(QWidget* parent)
    : QWidget(parent), p_impl(std::make_unique<GraphCanvasImpl>())
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(p_impl->custom_plot);
    layout->addWidget(p_impl->status_label);
    setLayout(layout);

    setMouseTracking(true);
    p_impl->customPlot()->setMouseTracking(true);
    p_impl->customPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_impl->customPlot()->axisRect()->setupFullAxesBox(true);
}

void GraphCanvas::setItem(GraphViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}

GraphCanvas::~GraphCanvas() = default;
