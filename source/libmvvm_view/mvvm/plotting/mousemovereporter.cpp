// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/mousemovereporter.h"
#include "mvvm/plotting/mouseposinfo.h"
#include <qcustomplot.h>
#include <QMouseEvent>
#include <memory>
#include <stdexcept>
#include <utility>

using namespace ModelView;

struct MouseMoveReporter::MouseMoveReporterImpl {
    MouseMoveReporter* const m_reporter{nullptr};
    QCustomPlot* const m_custom_plot{nullptr};
    const callback_t m_callback;
    MouseMoveReporterImpl(MouseMoveReporter* reporter, QCustomPlot* custom_plot,
                          callback_t callback)
        : m_reporter(reporter), m_custom_plot(custom_plot), m_callback(std::move(callback))
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
            if (m_callback)
                m_callback({x, y, axesRangeContains(x, y)});
        };

        QObject::connect(m_custom_plot, &QCustomPlot::mouseMove, on_mouse_move);
    }

    double pixelToXaxisCoord(double pixel) const { return m_custom_plot->m_xAxis->pixelToCoord(pixel); }

    double pixelToYaxisCoord(double pixel) const { return m_custom_plot->m_yAxis->pixelToCoord(pixel); }

    bool axesRangeContains(double xpos, double ypos) const
    {
        return m_custom_plot->m_xAxis->range().contains(xpos)
               && m_custom_plot->m_yAxis->range().contains(ypos);
    }
};

MouseMoveReporter::MouseMoveReporter(QCustomPlot* custom_plot, callback_t callback)
    : p_impl(std::make_unique<MouseMoveReporterImpl>(this, custom_plot, callback))
{
}

MouseMoveReporter::~MouseMoveReporter() = default;
