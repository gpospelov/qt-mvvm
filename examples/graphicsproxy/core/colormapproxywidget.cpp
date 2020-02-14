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
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
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

void ColorMapProxyWidget::setBlockSignalsToProxy(bool value)
{
    block_signals_to_proxy = value;
}

void ColorMapProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mousePressEvent(event);
}

void ColorMapProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mouseMoveEvent(event);
}

void ColorMapProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}

void ColorMapProxyWidget::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::wheelEvent(event);
}
