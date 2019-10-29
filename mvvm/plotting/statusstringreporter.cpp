// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "statusstringreporter.h"
#include "statusstringformatterinterface.h"
#include <QMouseEvent>
#include <qcustomplot.h>

using namespace ModelView;

struct StatusStringReporter::StatusStringReporterImpl {
    StatusStringReporter* reporter{nullptr};
    QCustomPlot* custom_plot{nullptr};
    callback_t callback;
    std::unique_ptr<StatusStringFormatterInterface> fmt;

    StatusStringReporterImpl(StatusStringReporter* reporter, QCustomPlot* custom_plot,
                             callback_t callback, std::unique_ptr<StatusStringFormatterInterface> formatter)
        : reporter(reporter), custom_plot(custom_plot), callback(callback), fmt(std::move(formatter))
    {
        if (!custom_plot)
            throw std::runtime_error("StatusStringReporter: not initialized custom plot.");
    }

    ~StatusStringReporterImpl() = default;
};

StatusStringReporter::StatusStringReporter(QCustomPlot* custom_plot, callback_t callback, std::unique_ptr<StatusStringFormatterInterface> formatter)
    : p_impl(std::make_unique<StatusStringReporterImpl>(this, custom_plot, callback, std::move(formatter)))
{
}

StatusStringReporter::~StatusStringReporter() = default;
