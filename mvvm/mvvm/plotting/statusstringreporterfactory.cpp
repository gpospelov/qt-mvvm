// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "statusstringreporterfactory.h"
#include "statusstringreporter.h"
#include "colormapinfoformatter.h"
#include "graphinfoformatter.h"

namespace ModelView
{

std::unique_ptr<StatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return std::make_unique<StatusStringReporter>(custom_plot, callback,
                                                  std::make_unique<GraphInfoFormatter>());
}

std::unique_ptr<StatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return std::make_unique<StatusStringReporter>(custom_plot, callback,
                                                  std::make_unique<ColorMapInfoFormatter>());
}

}

