// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/customplotproxywidget.h"
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QWidget>

using namespace ModelView;

CustomPlotProxyWidget::CustomPlotProxyWidget(QWidget* colormap)
{
    setWidget(colormap);
    colormap->installEventFilter(this);
}

//! Notifies all graphics items about axes viewport change in QCustomPlot.
//! Used in RegionOfInterestView to recalculate bounding box and scene positions depending on
//! current state of CustomPlotSceneAdapter.

bool CustomPlotProxyWidget::eventFilter(QObject* /*object*/, QEvent* event)
{
    // catching zoom/resize events in QCustomPlot
    if (event->type() == QEvent::Resize || event->type() == QEvent::UpdateRequest) {
        scene()->advance(); // notifying all graphics items
        return false;
    }
    return true;
}

void CustomPlotProxyWidget::setBlockSignalsToProxy(bool value)
{
    block_signals_to_proxy = value;
}

void CustomPlotProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mousePressEvent(event);
}

void CustomPlotProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mouseMoveEvent(event);
}

void CustomPlotProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::mouseReleaseEvent(event);
}

void CustomPlotProxyWidget::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    if (block_signals_to_proxy)
        return;
    QGraphicsProxyWidget::wheelEvent(event);
}
