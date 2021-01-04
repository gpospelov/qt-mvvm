// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "nodeport.h"
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

//! Returns port type. Input and output ports of the same type are compatible.

QString NodePort::portType() const
{
    return m_portType;
}

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

// ----------------------------------------------------------------------------

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
    setPos(0.0, parentItem()->boundingRect().height() * 0.4);
}

// ----------------------------------------------------------------------------

bool NodeOutputPort::isInput() const
{
    return false;
}

//! Initializes port position and labels.

void NodeOutputPort::initPort()
{
    // initializing label and its position
    m_label->setPlainText("Out");
    m_label->setPos(-port_radius() * 1.5 - m_label->boundingRect().width(),
                    -m_label->boundingRect().height() / 2);

    // initializing port position
    setPos(parentItem()->boundingRect().width(), parentItem()->boundingRect().height() * 0.4);
}

} // namespace NodeEditor
