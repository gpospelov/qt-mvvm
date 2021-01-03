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
            return true;
        }
    }
    return false;
}

bool NodeController::processMouseMove(QGraphicsSceneMouseEvent* event)
{
    if (m_conn) {
        m_conn->setPos2(event->scenePos());
        m_conn->updatePath();
        return true;
    }
    return false;
}

bool NodeController::processMouseRelease(QGraphicsSceneMouseEvent* event)
{
    if (m_conn && event->button() == Qt::LeftButton) {
        if (auto port2 = findPort(event->scenePos()); port2) {
            auto port1 = m_conn->port1();

            //            if (port1->parentItem() != port2->parentItem() && port1->isOutput() !=
            //            port2->isOutput()
            //                && !port1->isConnected(port2) && port1->getPortType() ==
            //                port2->getPortType()) { m_conn->setPos2(port2->scenePos());
            //                m_conn->setPort2(port2);
            //                m_conn->updatePath();
            //                emit connectionIsEstablished(m_conn);
            //                m_conn = 0;
            //                return true;
            //            }
        }
        delete m_conn;
        m_conn = nullptr;
        return true;
    }
    return false;
}

} // namespace NodeEditor
