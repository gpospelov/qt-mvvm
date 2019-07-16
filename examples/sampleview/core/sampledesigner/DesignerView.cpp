// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/DesignerView.cpp
//! @brief     Implements class DesignerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DesignerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"
#include "DesignerScene.h"
#include "GUIHelpers.h"
#include <QDragEnterEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMimeData>
#include <QShortcut>
#include <QVBoxLayout>

DesignerView::DesignerView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
    setAcceptDrops(true);
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    setDragMode(QGraphicsView::RubberBandDrag);
}

int DesignerView::getSelectionMode() const
{
    if (dragMode() == QGraphicsView::NoDrag) {
        return SIMPLE_SELECTION;
    } else if (dragMode() == QGraphicsView::RubberBandDrag) {
        return RUBBER_SELECTION;
    } else if (dragMode() == QGraphicsView::ScrollHandDrag) {
        return HAND_DRAG;
    } else {
        throw GUIHelpers::Error("DesignerView::getSelectionMode() -> Error.");
    }
}

void DesignerView::onSelectionMode(int mode)
{
    switch (mode) {
    case SIMPLE_SELECTION:
        setDragMode(QGraphicsView::NoDrag);
        setInteractive(true);
        emit selectionModeChanged(SIMPLE_SELECTION);
        break;
    case RUBBER_SELECTION:
        setDragMode(QGraphicsView::RubberBandDrag);
        setInteractive(true);
        emit selectionModeChanged(RUBBER_SELECTION);
        break;
    case HAND_DRAG:
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
        emit selectionModeChanged(HAND_DRAG);
        break;
    default:
        break;
    }
}

void DesignerView::onCenterView()
{
    // fitInView(scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
    centerOn(scene()->itemsBoundingRect().center());
}

void DesignerView::onChangeScale(double new_scale)
{
    QMatrix oldMatrix = matrix();
    resetMatrix();
    translate(oldMatrix.dx(), oldMatrix.dy());
    scale(new_scale, new_scale);
    DesignerHelper::setZoomLevel(new_scale);
}

void DesignerView::deleteSelectedItems()
{
    DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
    Q_ASSERT(designerScene);
    designerScene->deleteSelectedItems();
}

void DesignerView::zoomIn()
{
}

void DesignerView::zoomOut()
{
}

void DesignerView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Space:
        if (getSelectionMode() != HAND_DRAG && !event->isAutoRepeat()) {
            onSelectionMode(HAND_DRAG);
        }
        break;
    case Qt::Key_Delete:
        deleteSelectedItems();
        break;
    case Qt::Key_Backspace:
        deleteSelectedItems();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void DesignerView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:

        if (getSelectionMode() != RUBBER_SELECTION && !event->isAutoRepeat()) {
            onSelectionMode(RUBBER_SELECTION); // space released
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
