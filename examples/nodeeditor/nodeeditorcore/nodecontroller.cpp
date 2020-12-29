// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "nodecontroller.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

namespace NodeEditor {

NodeController::NodeController(QGraphicsScene* scene) : m_scene(scene)
{
    setParent(m_scene);
    m_scene->installEventFilter(this);
}

bool NodeController::eventFilter(QObject* object, QEvent* event)
{
    bool isProcessedEvent(false);

    if (auto mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event); mouseEvent) {
        if (event->type() == QEvent::GraphicsSceneMousePress)
            isProcessedEvent = processMousePress(mouseEvent);
        else if (event->type() == QEvent::GraphicsSceneMouseMove)
            isProcessedEvent = processMouseMove(mouseEvent);
        else if (event->type() == QEvent::GraphicsSceneMouseRelease)
            isProcessedEvent = processMouseRelease(mouseEvent);
    }

    return isProcessedEvent ? isProcessedEvent : QObject::eventFilter(object, event);
}

bool NodeController::processMousePress(QGraphicsSceneMouseEvent* event)
{
    return false;
}

bool NodeController::processMouseMove(QGraphicsSceneMouseEvent* event)
{
    return false;
}

bool NodeController::processMouseRelease(QGraphicsSceneMouseEvent* event)
{
    return false;
}

} // namespace NodeEditor
