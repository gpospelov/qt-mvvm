// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_STATUSSTRINGREPORTERFACTORY_H
#define MVVM_STATUSSTRINGREPORTERFACTORY_H

/*!
@file statusstringreporterfactory.h
@brief Contains factory methods to create StatusStringReporter
*/

#include <mvvm/core/export.h>
#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView
{

class StatusStringReporter;

//! Creates reporter for status string in QCustomPlot containing graphs.
CORE_EXPORT std::unique_ptr<StatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

//! Creates reporter for status string in QCustomPlot containing QCPColorMap.
CORE_EXPORT std::unique_ptr<StatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

} // namespace ModelView

#endif // MVVM_GRAPHCANVAS_H
