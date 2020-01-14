// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ConnectableView.h"
#include "DesignerHelper.h"
#include "NodeEditorConnection.h"
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <mvvm/model/sessionitem.h>

namespace
{
void setPortPositions(const QRectF frame, qreal x_pos, const QList<NodeEditorPort*>& nodes);
}

ConnectableView::ConnectableView(QGraphicsItem* parent, int view_type, QRectF rect)
    : IView(parent, view_type), m_color(Qt::gray), m_rect(rect), m_roundpar(3), m_label_vspace(35)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

ConnectableView::~ConnectableView() = default;

void ConnectableView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getDecorationGradient(m_color, getRectangle()));
    painter->drawRoundedRect(getRectangle(), m_roundpar, m_roundpar);

    if (m_label.isEmpty())
        return;

    painter->setPen(Qt::black);
    double width = getRectangle().width() * 0.9;
    double yoffset = 5; // space above the label
    double height = m_label_vspace - yoffset;
    QFont serifFont("Monospace", DesignerHelper::getLabelFontSize(), QFont::Normal);
    painter->setFont(serifFont);
    QRectF textRect(getRectangle().x() + (getRectangle().width() - width) / 2.,
                    getRectangle().y() + yoffset, width, height);
    painter->drawText(textRect, Qt::AlignCenter, m_label);
}

NodeEditorPort* ConnectableView::addPort(const QString& name,
                                         NodeEditorPort::EPortDirection direction,
                                         NodeEditorPort::EPortType port_type)
{
    NodeEditorPort* port = new NodeEditorPort(this, name, direction, port_type);
    if (direction == NodeEditorPort::INPUT) {
        m_input_ports.append(port);
    } else if (direction == NodeEditorPort::OUTPUT) {
        m_output_ports.append(port);
    } else {
        throw std::runtime_error("ConnectableView::addPort() -> Unknown port type");
    }
    setPortCoordinates();
    return port;
}

void ConnectableView::setLabel(const QString& name)
{
    m_label = name;
    setPortCoordinates();
}

void ConnectableView::connectInputPort(ConnectableView* other, int port_number)
{
    Q_ASSERT(other);

    if (port_number >= m_input_ports.size())
        throw std::runtime_error("ConnectableView::connectInputPort() -> Wrong input port number");

    if (other->getOutputPorts().size() != 1)
        throw std::runtime_error("ConnectableView::connectInputPort() -> Wrong output port number");

    if (port_number < 0)
        return;

    NodeEditorPort* input = m_input_ports.at(port_number);
    NodeEditorPort* output = other->getOutputPorts().at(0);

    if (!input->isConnected(output)) {
        NodeEditorConnection* conn = new NodeEditorConnection(scene());
        conn->setPort2(input);
        conn->setPort1(output);
        conn->updatePath();
    }
}

int ConnectableView::getInputPortIndex(NodeEditorPort* port)
{
    return m_input_ports.indexOf(port);
}

// calculation of y-pos for ports
void ConnectableView::setPortCoordinates()
{
    const QRectF rect = getRectangle();
    ::setPortPositions(rect, rect.left(), m_input_ports);
    ::setPortPositions(rect, rect.right(), m_output_ports);
}

int ConnectableView::getNumberOfPorts()
{
    return m_input_ports.size() + m_output_ports.size();
}

int ConnectableView::getNumberOfOutputPorts()
{
    return m_output_ports.size();
}

int ConnectableView::getNumberOfInputPorts()
{
    return m_input_ports.size();
}

void ConnectableView::update_appearance()
{
    setLabel(hyphenate(QString::fromStdString(getItem()->displayName())));
    IView::update_appearance();
}

QString ConnectableView::hyphenate(const QString& name) const
{
    QRegExp capital_letter("[A-Z]");
    QRegExp number("[0-9]");
    int next_capital = capital_letter.indexIn(name, 1);
    int next_number = number.indexIn(name, 1);
    if (next_capital > 0 && next_capital < name.size() - 2) {
        int first_split_index =
            (next_number > 0 && next_number < next_capital) ? next_number : next_capital;
        QString result = name.left(first_split_index) + QString("\n")
                         + name.right(name.size() - first_split_index);
        return result;
    }
    return name;
}

namespace
{
void setPortPositions(const QRectF frame, qreal x_pos, const QList<NodeEditorPort*>& nodes)
{
    if (nodes.empty())
        return;

    const qreal dy = frame.height() / (nodes.size() + 1);
    qreal y_pos = nodes.size() == 1 ? (frame.top() + frame.bottom()) / 2.0 : frame.top() + dy;
    std::for_each(nodes.begin(), nodes.end(), [&y_pos, x_pos, dy](NodeEditorPort* port) {
        port->setPos(x_pos, y_pos);
        y_pos += dy;
    });
}
} // namespace
