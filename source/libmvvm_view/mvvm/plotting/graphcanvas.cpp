// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <QBoxLayout>
#include <mvvm/plotting/customplotsceneadapter.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/plotting/graphviewportplotcontroller.h>
#include <mvvm/plotting/statusstringreporter.h>
#include <mvvm/plotting/statusstringreporterfactory.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/widgets/statuslabel.h>
#include <QDebug>

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

    //! Updates viewport.
    void update_viewport()
    {
        if (!viewport_controller->currentItem())
            return;
        viewport_controller->currentItem()->update_viewport();
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

    auto on_replot = [this]() {
        QMargins margins = p_impl->customPlot()->axisRect()->margins();
        qDebug() << "xxx " << margins;
        axisMarginsChanged(margins.left(), margins.top(), margins.right(), margins.bottom());
    };
    connect(p_impl->customPlot(), &QCustomPlot::afterReplot, this, on_replot);
}

GraphCanvas::~GraphCanvas() = default;

void GraphCanvas::setItem(GraphViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}

std::unique_ptr<SceneAdapterInterface> GraphCanvas::createSceneAdapter() const
{
    return std::make_unique<CustomPlotSceneAdapter>(p_impl->customPlot());
}

void GraphCanvas::update_viewport()
{
    p_impl->update_viewport();
}

//! Set margins between axes rectangle and widget borders.
//! If the value is negative, leave old margin intact.

void GraphCanvas::setAxisMargins(int left, int top, int right, int bottom)
{
    auto customPlot = p_impl->customPlot();
    QMargins orig = customPlot->axisRect()->margins();
    int new_left = left >= 0 ? left : orig.left();
    int new_top = top >= 0 ? top : orig.top();
    int new_right = right >= 0 ? right : orig.right();
    int new_bottom = bottom >= 0 ? bottom : orig.bottom();
    customPlot->axisRect()->setMargins(QMargins(new_left, new_top, new_right, new_bottom));
    customPlot->replot();
}
