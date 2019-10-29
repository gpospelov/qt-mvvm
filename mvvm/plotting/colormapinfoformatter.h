// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLORMAPINFOFORMATTER_H
#define MVVM_COLORMAPINFOFORMATTER_H

#include "statusstringformatterinterface.h"

class QCustomPlot;

namespace ModelView
{

/*!
@class StatusStringReporter
@brief Reports back status string composed for current mouse position in QCustomPlot.

Doesn't report if cursor is outside of the axes range.
*/

class CORE_EXPORT ColorMapInfoFormatter : public StatusStringFormatterInterface
{
public:
    std::string status_string(QCustomPlot* custom_plot, double x, double y) const override;
};

} // namespace ModelView

#endif // MVVM_COLORMAPINFOFORMATTER_H
