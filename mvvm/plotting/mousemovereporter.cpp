// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "mousemovereporter.h"
#include <qcustomplot.h>

using namespace ModelView;

struct MouseMoveReporter::MouseMoveReporterImpl {
    MouseMoveReporter* reporter{nullptr};
    QCustomPlot* custom_plot{nullptr};
    MouseMoveReporterImpl(MouseMoveReporter* reporter, QCustomPlot* custom_plot)
        : reporter(reporter), custom_plot(custom_plot)
    {
        if (!custom_plot)
            throw std::runtime_error("MouseMoveReporter: not initialized custom plot.");
    }
};

MouseMoveReporter::MouseMoveReporter(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<MouseMoveReporterImpl>(this, custom_plot))
{
}

ModelView::MouseMoveReporter::~MouseMoveReporter() = default;
