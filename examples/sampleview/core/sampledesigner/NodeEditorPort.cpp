// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/NodeEditorPort.cpp
//! @brief     Implements class NodeEditorPort
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "NodeEditorPort.h"
#include "NodeEditorConnection.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>

NodeEditorPort::NodeEditorPort(QGraphicsItem *parent, const QString &name,
                               NodeEditorPort::EPortDirection direction,
                               NodeEditorPort::EPortType port_type)
    : QGraphicsPathItem(parent), m_name(name), m_direction(direction), m_port_type(port_type),
      m_radius(5), m_margin(2), m_label(nullptr)
{
    m_color = getPortTypeColor(port_type);

    QPainterPath p;
    p.addEllipse(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
    setPath(p);

    setPen(QPen(m_color.darker(180)));
    setBrush(m_color);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

    if (!m_name.isEmpty()) {
        setLabel(m_name);
    }
}

NodeEditorPort::~NodeEditorPort()
{
    while (m_connections.size()>0) {
        auto conn = m_connections.last();
        conn->setSelected(false);
        delete conn;
    }
}

bool NodeEditorPort::isOutput()
{
    return (m_direction == OUTPUT ? true : false);
}

bool NodeEditorPort::isInput()
{
    return !isOutput();
}

void NodeEditorPort::remove(NodeEditorConnection *connection)
{
    if(m_connections.contains(connection))
        m_connections.remove(m_connections.indexOf(connection));
}

void NodeEditorPort::append(NodeEditorConnection *connection)
{
   m_connections.append(connection);
}

bool NodeEditorPort::isConnected(NodeEditorPort *other)
{
    for(auto conn : m_connections)
        if (conn->port1() == other || conn->port2() == other)
            return true;

    return false;
}

QColor NodeEditorPort::getPortTypeColor(NodeEditorPort::EPortType port_type)
{
    switch (port_type) {
    case DEFAULT:
        return QColor(Qt::gray);
    case INTERFERENCE:
        return QColor(Qt::yellow);
    case PARTICLE_LAYOUT:
        return QColor(Qt::green);
    case FORM_FACTOR:
        return QColor(Qt::blue);
    case TRANSFORMATION:
        return QColor(Qt::magenta);
    default:
        return QColor(Qt::red);
    }
}

QVariant NodeEditorPort::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged) {
        for(auto conn : m_connections) {
            conn->updatePosFromPorts();
            conn->updatePath();
        }
    }
    return value;
}

void NodeEditorPort::setLabel(QString name)
{
    if(!m_label)
        m_label = new QGraphicsTextItem(this);
    m_label->setPlainText(name);
    QFont serifFont("Monospace", DesignerHelper::getPortFontSize(), QFont::Normal);
    m_label->setFont(serifFont);

    if (isOutput()) {
        m_label->setPos(-m_radius - m_margin - m_label->boundingRect().width(),
                      -m_label->boundingRect().height() / 2);
    } else {
        m_label->setPos(m_radius + m_margin, -m_label->boundingRect().height() / 2);
    }
}


