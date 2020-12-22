// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H
#define MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H

//! Contains factory methods to create StatusStringReporter

#include "mvvm/view_export.h"
#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView {

class StatusStringReporter;

//! Creates reporter for status string in QCustomPlot containing graphs.
MVVM_VIEW_EXPORT std::unique_ptr<StatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

//! Creates reporter for status string in QCustomPlot containing QCPColorMap.
MVVM_VIEW_EXPORT std::unique_ptr<StatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

} // namespace ModelView

#endif // MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H
