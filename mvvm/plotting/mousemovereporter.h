// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_MOUSEMOVEREPORTER_H
#define MVVM_MOUSEMOVEREPORTER_H

#include "mvvm_export.h"
#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView
{

/*!
@class MouseMoveReporter
@brief Tracks mouse moves in QCustomPlot canvas.

Notifies client about mouse moves and corresponding data in QCustomPlot.
*/

class CORE_EXPORT MouseMoveReporter
{
public:
    MouseMoveReporter(QCustomPlot* custom_plot);
    ~MouseMoveReporter();

private:
    struct MouseMoveReporterImpl;
    std::unique_ptr<MouseMoveReporterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_MOUSEMOVEREPORTER_H
