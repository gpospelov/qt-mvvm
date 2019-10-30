// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapcanvas.h"
#include "colormapinfoformatter.h"
#include "colormapviewportitem.h"
#include "colormapviewportplotcontroller.h"
#include "qcustomplot.h"
#include "statuslabel.h"
#include "statusstringreporter.h"
#include <QBoxLayout>
#include <QDebug>

using namespace ModelView;

struct ColorMapCanvas::ColorMapCanvasPrivate {
    QCustomPlot* custom_plot{nullptr};
    std::unique_ptr<ColorMapViewportPlotController> viewport_controller;
    std::unique_ptr<StatusStringReporter> reporter;
    StatusLabel* status_label{nullptr};

    ColorMapCanvasPrivate()
        : custom_plot(new QCustomPlot), status_label(new StatusLabel)
    {
        viewport_controller = std::make_unique<ColorMapViewportPlotController>(custom_plot);

        auto on_mouse_move = [this](const std::string& str) {
            status_label->setText(QString::fromStdString(str));
        };
        reporter = std::make_unique<StatusStringReporter>(
            custom_plot, on_mouse_move, std::make_unique<ColorMapInfoFormatter>());
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

ColorMapCanvas::ColorMapCanvas(QWidget* parent)
    : QWidget(parent), p_impl(std::make_unique<ColorMapCanvasPrivate>())
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(p_impl->custom_plot);
    layout->addWidget(p_impl->status_label);
    setLayout(layout);

    p_impl->customPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_impl->customPlot()->axisRect()->setupFullAxesBox(true);
}

ColorMapCanvas::~ColorMapCanvas() = default;

void ColorMapCanvas::setItem(ColorMapViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}
