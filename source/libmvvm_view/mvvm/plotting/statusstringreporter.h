// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_STATUSSTRINGREPORTER_H
#define MVVM_PLOTTING_STATUSSTRINGREPORTER_H

#include "mvvm/view_export.h"
#include <functional>
#include <memory>
#include <string>

class QCustomPlot;

namespace ModelView {

class StatusStringFormatterInterface;

//! Reports back status string composed for current mouse position in QCustomPlot.
//! Doesn't report if cursor is outside of the axes range.

class MVVM_VIEW_EXPORT StatusStringReporter {
public:
    using callback_t = std::function<void(const std::string&)>;
    StatusStringReporter(QCustomPlot* custom_plot, callback_t callback,
                         std::unique_ptr<StatusStringFormatterInterface> formatter);
    ~StatusStringReporter();

private:
    struct StatusStringReporterImpl;
    std::unique_ptr<StatusStringReporterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_STATUSSTRINGREPORTER_H
