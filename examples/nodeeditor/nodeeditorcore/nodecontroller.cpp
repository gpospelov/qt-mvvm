// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "nodecontroller.h"
#include "nodeport.h"
#include "nodeconnection.h"
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
    bool result(false);

    if (!m_conn && event->button() == Qt::LeftButton) {
        if (auto port = findPort(event->scenePos()); port) {
            m_conn = new NodeConnection(m_scene);
        }

//        QGraphicsItem* item = itemAt(event->scenePos());
//        if (item && item->type() == ViewTypes::NODE_EDITOR_PORT) {
//            emit selectionModeChangeRequest(DesignerView::SIMPLE_SELECTION);
//            m_conn = new NodeEditorConnection(0, m_scene);
//            m_conn->setPort1((NodeEditorPort*)item);
//            m_conn->setPos1(item->scenePos());
//            m_conn->setPos2(event->scenePos());
//            m_conn->updatePath();

//            result = true;
//        }
    }
    return result;
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
