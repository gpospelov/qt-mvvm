// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/colormapcanvas.h"
#include "mvvm/plotting/colormapviewportplotcontroller.h"
#include "mvvm/plotting/customplotsceneadapter.h"
#include "mvvm/plotting/statusstringreporter.h"
#include "mvvm/plotting/statusstringreporterfactory.h"
#include "mvvm/standarditems/colormapviewportitem.h"
#include "mvvm/widgets/statuslabel.h"
#include <qcustomplot.h>

using namespace ModelView;

struct ColorMapCanvas::ColorMapCanvasImpl {
    QCustomPlot* custom_plot{nullptr};
    std::unique_ptr<ColorMapViewportPlotController> viewport_controller;
    std::unique_ptr<StatusStringReporter> reporter;
    StatusLabel* status_label{nullptr};

    ColorMapCanvasImpl() : custom_plot(new QCustomPlot), status_label(new StatusLabel)
    {
        viewport_controller = std::make_unique<ColorMapViewportPlotController>(custom_plot);

        auto on_mouse_move = [this](const std::string& str) {
            status_label->setText(QString::fromStdString(str));
        };
        reporter = CreateColorMapReporter(custom_plot, on_mouse_move);
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

ColorMapCanvas::ColorMapCanvas(QWidget* parent)
    : QWidget(parent), p_impl(std::make_unique<ColorMapCanvasImpl>())
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

//! Creates adapter to convert widget coordinates, to QCustomPlot internal coordinate system
//! (defined by its axes).

std::unique_ptr<SceneAdapterInterface> ColorMapCanvas::createSceneAdapter() const
{
    return std::make_unique<CustomPlotSceneAdapter>(p_impl->customPlot());
}
