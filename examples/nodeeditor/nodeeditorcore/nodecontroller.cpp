// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "nodecontroller.h"
#include "nodeconnection.h"
#include "nodeport.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

namespace {
const bool event_was_handled = true;
const bool event_was_ignored = false;
} // namespace

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

    return isProcessedEvent ? event_was_handled : QObject::eventFilter(object, event);
}

//! Finds NodePort around given coordinate.

NodePort* NodeController::findPort(const QPointF& pos)
{
    QRectF area(0, 0, 4, 4);
    area.moveCenter(pos);

    for (auto item : m_scene->items(area))
        if (auto port = dynamic_cast<NodePort*>(item); port)
            return port;
    return nullptr;
}

bool NodeController::processMousePress(QGraphicsSceneMouseEvent* event)
{
    if (!m_conn && event->button() == Qt::LeftButton) {
        if (auto port = findPort(event->scenePos()); port) {
            m_conn = new NodeConnection(m_scene);
            m_conn->setPort1(port);
            m_conn->setPos1(port->scenePos());
            m_conn->setPos2(event->scenePos());
            m_conn->updatePath();
            return event_was_handled;
        }
    }
    return event_was_ignored;
}

bool NodeController::processMouseMove(QGraphicsSceneMouseEvent* event)
{
    if (m_conn) {
        m_conn->setPos2(event->scenePos());
        m_conn->updatePath();
        return event_was_handled;
    }
    return event_was_ignored;
}

bool NodeController::processMouseRelease(QGraphicsSceneMouseEvent* event)
{
    if (m_conn && event->button() == Qt::LeftButton) {
        if (auto port2 = findPort(event->scenePos()); port2) {
            auto port1 = m_conn->port1();
            if (port1->isConnectable(port2)) {
                m_conn->setPort2(port2);
                m_conn->updatePath();

                // At this point we do not need NodeConnection object anymore.
                // It will be redrawn automatically, when the model process our request.

                auto child = m_conn->childView();
                auto parent = m_conn->parentView();
                resetConnection();

                // Sending request for connection.
                emit connectionRequest(child, parent);
            }
        }
        resetConnection();
        return event_was_handled;
    }
    return event_was_ignored;
}

void NodeController::resetConnection()
{
    delete m_conn;
    m_conn = nullptr;
}

} // namespace NodeEditor
