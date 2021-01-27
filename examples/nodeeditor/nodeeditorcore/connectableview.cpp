// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "connectableview.h"
#include "connectableitemcontroller.h"
#include "nodeconnection.h"
#include "nodeport.h"
#include "sampleitems.h"
#include "sceneutils.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace {
const int round_par = 5;

//! Returns rectangle to display ConnectableView label. Takes bounding box of a view as input
//! parameter.
QRectF label_rectangle(const QRectF& rect)
{
    return QRectF(rect.x(), rect.y(), rect.width(), rect.height() / 4);
}

} // namespace

namespace NodeEditor {

ConnectableView::ConnectableView(ConnectableItem* item)
    : m_item(item), m_controller(std::make_unique<ConnectableItemController>(item, this))
{
    m_rect = ConnectableViewRectangle();

    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    init_ports();
}

ConnectableView::~ConnectableView() = default;

QRectF ConnectableView::boundingRect() const
{
    return m_rect;
}

void ConnectableView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus))
        painter->setPen(Qt::DashLine);

    painter->setBrush(ConnectableViewGradient(color(), boundingRect()));
    painter->drawRoundedRect(boundingRect(), round_par, round_par);

    painter->setPen(Qt::black);
    QFont serifFont("Monospace", 8, QFont::Normal);
    painter->setFont(serifFont);
    painter->drawText(label_rectangle(boundingRect()), Qt::AlignCenter, label());
}

//! Connects children's output port to appropriate input port.

void ConnectableView::makeChildConnected(ConnectableView* childView)
{
    auto output = childView->outputPort();
    if (!output)
        return;

    for (auto input : inputPorts()) {
        if (input->isConnectable(output)) {
            auto connection = new NodeConnection(scene()); // ownership to scene
            connection->setPort2(input);
            connection->setPort1(output);
            connection->updatePath();
        }
    }
}

//! Returns list of input ports of given

QList<NodeInputPort*> ConnectableView::inputPorts() const
{
    return ports<NodeInputPort>();
}

NodeOutputPort* ConnectableView::outputPort() const
{
    auto output_ports = ports<NodeOutputPort>();
    return output_ports.empty() ? nullptr : output_ports.front();
}

ConnectableItem* ConnectableView::connectableItem() const
{
    return m_item;
}

QList<NodeConnection*> ConnectableView::inputConnections() const
{
    QList<NodeConnection*> result;
    for (auto port : inputPorts())
        result.append(port->connections());
    return result;
}

void ConnectableView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);
    m_controller->updateItemFromView();
}

//! Returns base color of this item.

QColor ConnectableView::color() const
{
    return m_item ? m_item->color() : QColor(Qt::red);
}

//! Returns label of this item.

QString ConnectableView::label() const
{
    return m_item ? QString::fromStdString(m_item->displayName()) : QString("Unnamed");
}

//! Init ports to connect.

void ConnectableView::init_ports()
{
    int portIndex{0};
    for (const auto& info : m_item->inputPorts()) {
        auto inputPort = new NodeInputPort(this, info);
        inputPort->initPort(portIndex++);
    }

    portIndex = 0;
    for (const auto& info : m_item->outputPorts()) {
        auto outputPort = new NodeOutputPort(this, info);
        outputPort->initPort(portIndex++);
    }
}

} // namespace NodeEditor
