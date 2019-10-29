// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mousemovereporter.h"
#include "mouseposinfo.h"
#include <qcustomplot.h>
#include <QMouseEvent>

using namespace ModelView;

struct MouseMoveReporter::MouseMoveReporterImpl {
    MouseMoveReporter* reporter{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    MouseMoveReporterImpl(MouseMoveReporter* reporter, QCustomPlot* custom_plot, callback_t callback)
        : reporter(reporter), custom_plot(custom_plot), callback(callback)
    {
        if (!custom_plot)
            throw std::runtime_error("MouseMoveReporter: not initialized custom plot.");

        custom_plot->setMouseTracking(true);
        set_connected();
    }

    void set_connected()
    {
        auto on_mouse_move = [this](QMouseEvent* event) {
            double x = pixelToXaxisCoord(event->pos().x());
            double y = pixelToYaxisCoord(event->pos().y());
            if (callback)
                callback({x, y, axesRangeContains(x, y)});
        };

        QObject::connect(custom_plot, &QCustomPlot::mouseMove, on_mouse_move);
    }

    double pixelToXaxisCoord(double pixel) const
    {
        return custom_plot->xAxis->pixelToCoord(pixel);
    }

    double pixelToYaxisCoord(double pixel) const
    {
        return custom_plot->yAxis->pixelToCoord(pixel);
    }

    bool axesRangeContains(double xpos, double ypos) const
    {
        return custom_plot->xAxis->range().contains(xpos) && custom_plot->yAxis->range().contains(ypos);
    }

};

MouseMoveReporter::MouseMoveReporter(QCustomPlot* custom_plot, callback_t callback)
    : p_impl(std::make_unique<MouseMoveReporterImpl>(this, custom_plot, callback))
{
}

MouseMoveReporter::~MouseMoveReporter() = default;
