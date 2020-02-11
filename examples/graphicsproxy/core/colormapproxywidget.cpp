// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "colormapproxywidget.h"
#include <QEvent>
#include <QGraphicsScene>
#include <mvvm/plotting/colormapcanvas.h>

ColorMapProxyWidget::ColorMapProxyWidget(ModelView::ColorMapCanvas* colormap)
{
    setWidget(colormap);
    colormap->installEventFilter(this);
}

//! Notifies all graphics items about axes viewport change in QCustomPlot.
//! Used in RegionOfInterestView to recalculate bounding box and scene positions depending on
//! current state of CustomPlotSceneAdapter.

bool ColorMapProxyWidget::eventFilter(QObject* /*object*/, QEvent* event)
{
    // catching zoom/resize events in QCustomPlot
    if (event->type() == QEvent::Resize || event->type() == QEvent::UpdateRequest) {
        scene()->advance(); // notifying all graphics items
        return false;
    }
    return true;
}
