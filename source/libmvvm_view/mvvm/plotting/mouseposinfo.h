// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_MOUSEPOSINFO_H
#define MVVM_PLOTTING_MOUSEPOSINFO_H

#include "mvvm/view_export.h"

class QCustomPlot;

namespace ModelView {

//! Aggregate to hold mouse position info in QCustomPlot context.
//! Position is given in axis coordinates corresponding to the current zoom level.

struct MVVM_VIEW_EXPORT MousePosInfo {
    double xpos{0.0};
    double ypos{0.0};
    bool in_axes_range{false};
};

} // namespace ModelView

#endif // MVVM_PLOTTING_MOUSEPOSINFO_H
