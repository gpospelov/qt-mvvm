// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_STATUSSTRINGREPORTER_H
#define MVVM_STATUSSTRINGREPORTER_H

#include "mvvm_export.h"
#include <functional>
#include <memory>
#include <string>

class QCustomPlot;

namespace ModelView
{

/*!
@class StatusStringReporter
@brief Reports back status string composed for current mouse position in QCustomPlot.

Doesn't report if cursor is outside of the axes range.
*/

class CORE_EXPORT StatusStringReporter
{
public:
    using callback_t = std::function<std::string()>;
    StatusStringReporter(QCustomPlot* custom_plot, callback_t callback);
    ~StatusStringReporter();

private:
    struct StatusStringReporterImpl;
    std::unique_ptr<StatusStringReporterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_STATUSSTRINGREPORTER_H
