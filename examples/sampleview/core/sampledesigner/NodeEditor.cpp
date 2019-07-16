// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/NodeEditor.cpp
//! @brief     Implements class NodeEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "NodeEditor.h"
#include "DesignerView.h"
#include "NodeEditorConnection.h"
#include "NodeEditorPort.h"
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

NodeEditor::NodeEditor(QObject *parent)
    : QObject(parent)
    , m_scene(0)
    , m_conn(0)
{}

void NodeEditor::install(QGraphicsScene *scene)
{
    scene->installEventFilter(this);
    m_scene = scene;
}

QGraphicsItem* NodeEditor::itemAt(const QPointF &pos)
{
    QList<QGraphicsItem*> items = m_scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

    for(QGraphicsItem* item : items)
        if (item->type() > QGraphicsItem::UserType)
            return item;

    return nullptr;
}

bool NodeEditor::eventFilter(QObject *object, QEvent *event)
{
    QGraphicsSceneMouseEvent *mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if(!mouseEvent)  return QObject::eventFilter(object, event);

    bool isProcessedEvent(false);

    if(event->type() == QEvent::GraphicsSceneMousePress) {
        isProcessedEvent = processMousePress(mouseEvent);
    }
    else if(event->type() == QEvent::GraphicsSceneMouseMove) {
        isProcessedEvent = processMouseMove(mouseEvent);
    }
    else if(event->type() == QEvent::GraphicsSceneMouseRelease) {
        isProcessedEvent = processMouseRelease(mouseEvent);
    }
    return isProcessedEvent ? isProcessedEvent : QObject::eventFilter(object, event);
}

bool NodeEditor::processMousePress(QGraphicsSceneMouseEvent *event)
{
    bool result(false);

    if(m_conn==0 && event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos());
        if (item && item->type() == NodeEditorPort::TYPE) {
            emit selectionModeChangeRequest(DesignerView::SIMPLE_SELECTION);
            m_conn = new NodeEditorConnection(0, m_scene);
            m_conn->setPort1((NodeEditorPort*) item);
            m_conn->setPos1(item->scenePos());
            m_conn->setPos2(event->scenePos());
            m_conn->updatePath();

            result = true;
        }
    }
    return result;
}

bool NodeEditor::processMouseMove(QGraphicsSceneMouseEvent *event)
{
    bool result(false);

    if (m_conn) {
        m_conn->setPos2(event->scenePos());
        m_conn->updatePath();
        result = true;
    }
    return result;
}

bool NodeEditor::processMouseRelease(QGraphicsSceneMouseEvent *event)
{
    bool result(false);

    if (m_conn && event->button() == Qt::LeftButton)
    {
        emit selectionModeChangeRequest(DesignerView::RUBBER_SELECTION);

        QGraphicsItem *item = itemAt(event->scenePos());
        if (item && item->type() == NodeEditorPort::TYPE)
        {
            NodeEditorPort *port1 = m_conn->port1();
            NodeEditorPort *port2 = (NodeEditorPort*) item;

            if (port1->parentItem() != port2->parentItem()
                    && port1->isOutput() != port2->isOutput()
                    && !port1->isConnected(port2)
                    && port1->getPortType() == port2->getPortType()
                    )
            {
                m_conn->setPos2(port2->scenePos());
                m_conn->setPort2(port2);
                m_conn->updatePath();
                emit connectionIsEstablished(m_conn);
                m_conn = 0;
                return true;
            }
        }
        delete m_conn;
        m_conn = 0;
        result = true;
    }
    return result;
}
