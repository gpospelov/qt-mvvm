// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/plotting/statusstringreporterfactory.h>
#include <mvvm/plotting/statusstringreporter.h>
#include <mvvm/plotting/colormapinfoformatter.h>
#include <mvvm/plotting/graphinfoformatter.h>

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

