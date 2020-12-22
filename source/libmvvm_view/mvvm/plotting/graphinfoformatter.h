// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHINFOFORMATTER_H
#define MVVM_PLOTTING_GRAPHINFOFORMATTER_H

#include "mvvm/plotting/statusstringformatterinterface.h"

class QCustomPlot;

namespace ModelView {

//! Formats status string for current mouse position in QCustomPlot with QCPGraph's.
//! Includes coordinates of mouse pointer in viewport axes coordinates, add graph info if there is
//! one nearby.

class MVVM_VIEW_EXPORT GraphInfoFormatter : public StatusStringFormatterInterface {
public:
    //! Returns status string representing graph nearby.
    //! @params x: mouse x-position given in axis viewport coordinates
    //! @params y: mouse y-position given in axis viewport coordinates
    std::string status_string(QCustomPlot* custom_plot, double x, double y) const override;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHINFOFORMATTER_H
