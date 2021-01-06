// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "nodeport.h"
#include "connectableview.h"
#include "nodeconnection.h"
#include "mvvm/widgets/widgetutils.h"
#include <QFont>
#include <QPen>

namespace {

double port_radius()
{
    return ModelView::Utils::WidthOfLetterM() * 0.4;
}

} // namespace

namespace NodeEditor {

NodePort::NodePort(QGraphicsItem* parent, QString portType)
    : QGraphicsPathItem(parent)
    , m_portType(std::move(portType))
    , m_label(new QGraphicsTextItem(this))
{
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    const double radius = port_radius();
    const QColor color(Qt::red);

    QPainterPath p;
    p.addEllipse(-radius, -radius, 2 * radius, 2 * radius);
    setPath(p);
    setPen(QPen(color.darker(180)));
    setBrush(color);

    QFont serifFont("Monospace", 8, QFont::Normal);
    m_label->setFont(serifFont);
}

NodePort::~NodePort()
{
    while (!m_connections.empty()) {
        auto conn = m_connections.last();
        conn->setSelected(false);
        delete conn;
    }
}

//! Returns port type. Input and output ports of the same type are compatible.

QString NodePort::portType() const
{
    return m_portType;
}

//! Returns true if this is a NodeOutputPort.

bool NodePort::isOutput() const
{
    return !isInput();
}

void NodePort::append(NodeConnection* connection)
{
    m_connections.append(connection);
}

void NodePort::remove(NodeConnection* connection)
{
    m_connections.removeAll(connection);
}

//! Returns true if this port can be connected with the other one.

bool NodePort::isConnectable(const NodePort& other) const
{
    bool different_parents = parentItem() != other.parentItem();
    bool output_to_input = isInput() != other.isInput();
    bool compatible_types = portType() == other.portType();
    bool not_already_connected = !isConnected(other);
    return different_parents && output_to_input && compatible_types && not_already_connected;
}

//! Returns true if ports are connected.

bool NodePort::isConnected(const NodePort& other) const
{
    for (auto conn : m_connections)
        if (conn->hasPort(other))
            return true;
    return false;
}

//! Returns parent to which this port belongs.

ConnectableView* NodePort::connectableView() const
{
    return dynamic_cast<ConnectableView*>(parentItem());
}

QVariant NodePort::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if (change == ItemScenePositionHasChanged) {
        for (auto conn : m_connections) {
            conn->updatePosFromPorts();
            conn->updatePath();
        }
    }
    return value;
}

// ----------------------------------------------------------------------------

//! Returns true if this is a NodeInputPort.

bool NodeInputPort::isInput() const
{
    return true;
}

//! Initializes port position and labels.

void NodeInputPort::initPort()
{
    // initializing label and its position
    m_label->setPlainText(m_portType.toLower());
    m_label->setPos(port_radius() * 1.5, -m_label->boundingRect().height() / 2);

    // initializing port position
    setPos(0.0, parentItem()->boundingRect().height() * 0.6);
}

// ----------------------------------------------------------------------------

//! Returns true if this is a NodeInputPort.

bool NodeOutputPort::isInput() const
{
    return false;
}

//! Initializes port position and labels.

void NodeOutputPort::initPort()
{
    // initializing label and its position
    m_label->setPlainText("out");
    m_label->setPos(-port_radius() * 1.5 - m_label->boundingRect().width(),
                    -m_label->boundingRect().height() / 2);

    // initializing port position
    setPos(parentItem()->boundingRect().width(), parentItem()->boundingRect().height() * 0.4);
}

} // namespace NodeEditor
