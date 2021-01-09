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
#include <QPainter>
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

void NodeConnection::updatePath()
{
    if (m_port1)
        m_pos1 = m_port1->scenePos();

    if (m_port2)
        m_pos2 = m_port2->scenePos();

    QPainterPath p;
    p.moveTo(m_pos1);
    qreal dx = m_pos2.x() - m_pos1.x();
    dx = qMax(dx, 200.);
    QPointF ctr1(m_pos1.x() + dx * 0.25, m_pos1.y());
    QPointF ctr2(m_pos2.x() - dx * 0.25, m_pos2.y());
    p.cubicTo(ctr1, ctr2, m_pos2);
    setPath(p);
}

//! Returns the port from where the connection begins.
//! It corresponds to the NodePort, on which the user has clicked first while connecting two ports.

NodePort* NodeConnection::port1() const
{
    return m_port1;
}

//! Returns true if given port belongs to this connection.

bool NodeConnection::hasPort(const NodePort* port) const
{
    return m_port1 == port || m_port2 == port;
}

void NodeConnection::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(Qt::darkGray, 2));
    painter->setBrush(Qt::NoBrush);

    if (isSelected())
        painter->setPen(Qt::DashLine);

    painter->drawPath(path());
}

//! Returns ConnectableView playing the role of a child.
//! By our convention, child has NodeOutputPort belonging to this connection.

ConnectableView* NodeConnection::childView() const
{
    auto output_port = m_port1->isOutput() ? m_port1 : m_port2;
    return output_port->connectableView();
}

//! Returns ConnectableView playing the role of a parent.
//! By our convention, the parent has NodeOutputPort belonging to this connection.

ConnectableView* NodeConnection::parentView() const
{
    auto input_port = m_port1->isInput() ? m_port1 : m_port2;
    return input_port->connectableView();
}

} // namespace NodeEditor
