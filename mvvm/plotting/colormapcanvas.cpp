// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapcanvas.h"
#include "qcustomplot.h"
#include "colormapviewportitem.h"
#include "colormapviewportplotcontroller.h"
#include <QBoxLayout>

using namespace ModelView;

struct ColorMapCanvas::ColorMapCanvasPrivate {
    QCustomPlot* custom_plot{nullptr};
    std::unique_ptr<ColorMapViewportPlotController> viewport_controller;

    ColorMapCanvasPrivate() : custom_plot(new QCustomPlot)
    {
        viewport_controller = std::make_unique<ColorMapViewportPlotController>(custom_plot);
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
    setLayout(layout);

    setMouseTracking(true);
    p_impl->customPlot()->setMouseTracking(true);
    p_impl->customPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_impl->customPlot()->axisRect()->setupFullAxesBox(true);
}

ColorMapCanvas::~ColorMapCanvas() = default;

void ColorMapCanvas::setItem(ColorMapViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}
