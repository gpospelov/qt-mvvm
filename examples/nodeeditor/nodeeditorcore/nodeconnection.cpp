// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "nodeconnection.h"
#include "nodeport.h"
#include <QGraphicsScene>
#include <QPen>

namespace NodeEditor {

NodeConnection::NodeConnection(QGraphicsScene* scene)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::darkGray, 2));
    setBrush(Qt::NoBrush);
    setZValue(-1);
    if (scene)
        scene->addItem(this);
}

NodeConnection::~NodeConnection()
{
    if (m_port1)
        m_port1->remove(this);

    if (m_port2)
        m_port2->remove(this);
}

void NodeConnection::setPos1(const QPointF& pos)
{
    m_pos1 = pos;
}

void NodeConnection::setPos2(const QPointF& pos)
{
    m_pos2 = pos;
}

void NodeConnection::setPort1(NodePort* port)
{
    m_port1 = port;
    m_port1->append(this);
    setPos1(port->scenePos());
}

void NodeConnection::setPort2(NodePort* port)
{
    m_port2 = port;
    m_port2->append(this);
    setPos2(port->scenePos());
}

void NodeConnection::updatePosFromPorts()
{
    m_pos1 = m_port1->scenePos();
    m_pos2 = m_port2->scenePos();
}

void NodeConnection::updatePath()
{
    QPainterPath p;
    p.moveTo(m_pos1);
    qreal dx = m_pos2.x() - m_pos1.x();
    dx = qMax(dx, 200.);
    QPointF ctr1(m_pos1.x() + dx * 0.25, m_pos1.y());
    QPointF ctr2(m_pos2.x() - dx * 0.25, m_pos2.y());
    p.cubicTo(ctr1, ctr2, m_pos2);
    setPath(p);
}

NodePort* NodeConnection::port1() const
{
    return m_port1;
}

//! Returns true if given port belongs to this connection.

bool NodeConnection::hasPort(const NodePort& port) const
{
    return m_port1 == &port || m_port2 == &port;
}

} // namespace NodeEditor
