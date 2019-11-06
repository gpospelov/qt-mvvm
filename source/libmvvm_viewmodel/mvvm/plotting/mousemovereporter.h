// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_PLOTTING_MOUSEMOVEREPORTER_H
#define MVVM_PLOTTING_MOUSEMOVEREPORTER_H

#include <mvvm/core/export.h>
#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView
{

class MousePosInfo;

/*!
@class MouseMoveReporter
@brief Tracks mouse moves in QCustomPlot canvas.

Notifies client about mouse moves and corresponding pointer coordinates expressed in axes units
at current zoom level.
*/

class CORE_EXPORT MouseMoveReporter
{
public:
    using callback_t = std::function<void(const MousePosInfo& pos_info)>;
    MouseMoveReporter(QCustomPlot* custom_plot, callback_t callback);
    ~MouseMoveReporter();

private:
    struct MouseMoveReporterImpl;
    std::unique_ptr<MouseMoveReporterImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_MOUSEMOVEREPORTER_H
