// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "statusstringreporter.h"
#include "mousemovereporter.h"
#include "mouseposinfo.h"
#include "statusstringformatterinterface.h"
#include <QMouseEvent>
#include <qcustomplot.h>

using namespace ModelView;

struct StatusStringReporter::StatusStringReporterImpl {
    StatusStringReporter* parent{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    std::unique_ptr<StatusStringFormatterInterface> fmt;
    std::unique_ptr<MouseMoveReporter> mouse_reporter;

    StatusStringReporterImpl(StatusStringReporter* parent, QCustomPlot* custom_plot,
                             callback_t callback,
                             std::unique_ptr<StatusStringFormatterInterface> formatter)
        : parent(parent), custom_plot(custom_plot), callback(callback), fmt(std::move(formatter))
    {
        if (!custom_plot)
            throw std::runtime_error("StatusStringReporter: not initialized custom plot.");

        auto on_mouse_move = [this](const MousePosInfo& pos) {
            this->callback(fmt->status_string(this->custom_plot, pos.xpos, pos.ypos));
        };

        mouse_reporter = std::make_unique<MouseMoveReporter>(custom_plot, on_mouse_move);
    }

    ~StatusStringReporterImpl() = default;
};

StatusStringReporter::StatusStringReporter(
    QCustomPlot* custom_plot, callback_t callback,
    std::unique_ptr<StatusStringFormatterInterface> formatter)
    : p_impl(std::make_unique<StatusStringReporterImpl>(this, custom_plot, callback,
                                                        std::move(formatter)))
{
}

StatusStringReporter::~StatusStringReporter() = default;
