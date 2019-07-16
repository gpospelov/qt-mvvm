// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ConnectableView.cpp
//! @brief     Implements class ConnectableView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ConnectableView.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "NodeEditorConnection.h"
#include "NodeEditorPort.h"
#include "SessionItem.h"
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <iostream>

ConnectableView::ConnectableView(QGraphicsItem *parent, QRectF rect)
    : IView(parent), m_name("Unnamed"), m_color(Qt::gray), m_rect(rect), m_roundpar(3),
      m_label_vspace(35)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void ConnectableView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
{
    Q_UNUSED(widget);

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

NodeEditorPort *ConnectableView::addPort(const QString &name,
                                         NodeEditorPort::EPortDirection direction,
                                         NodeEditorPort::EPortType port_type)
{
    NodeEditorPort *port = new NodeEditorPort(this, name, direction, port_type);
    if (direction == NodeEditorPort::INPUT) {
        m_input_ports.append(port);
    } else if (direction == NodeEditorPort::OUTPUT) {
        m_output_ports.append(port);
    } else {
        throw GUIHelpers::Error("ConnectableView::addPort() -> Unknown port type");
    }
    setPortCoordinates();
    return port;
}

void ConnectableView::setLabel(const QString &name)
{
    m_label = name;
    setPortCoordinates();
}

void ConnectableView::connectInputPort(ConnectableView *other, int port_number)
{
    Q_ASSERT(other);

    if (port_number >= m_input_ports.size())
        throw GUIHelpers::Error("ConnectableView::connectInputPort() -> Wrong input port number");

    if (other->getOutputPorts().size() != 1)
        throw GUIHelpers::Error("ConnectableView::connectInputPort() -> Wrong output port number");

    if (port_number < 0)
        return;

    NodeEditorPort *input = m_input_ports.at(port_number);
    NodeEditorPort *output = other->getOutputPorts().at(0);

    if (!input->isConnected(output)) {
        NodeEditorConnection *conn = new NodeEditorConnection(0, scene());
        conn->setPort2(input);
        conn->setPort1(output);
        conn->updatePath();
    }
}

int ConnectableView::getInputPortIndex(NodeEditorPort *port)
{
    return m_input_ports.indexOf(port);
}

// calculation of y-pos for ports
void ConnectableView::setPortCoordinates()
{
    if (!getNumberOfPorts())
        return;

    // without main label ports can be placed over all rectangle vertical space
    double hspace = getRectangle().height();
    if (!getLabel().isEmpty())
        hspace -= m_label_vspace;

    double nintervals = getNumberOfPorts()
                     + 2; // one spare interval for margin between input/output ports

    double dy = hspace / double(nintervals);
    double ypos = getRectangle().height() - hspace + dy;

    if (getNumberOfPorts() == 1) {
        // if total number of ports is 1, place it in the middle
        ypos = getRectangle().height() - hspace + hspace / 2;
    }
    int nOutPorts = getNumberOfOutputPorts();
    int nport(0);
    for(QGraphicsItem *item : childItems()) {
        NodeEditorPort *port = dynamic_cast<NodeEditorPort *>(item);
        if (!port)
            continue;
        if (port->isOutput()) {
            port->setPos(getRectangle().width(), ypos);
        } else {
            if (nport == nOutPorts && nOutPorts != 0)
                ypos += dy; // additional margin between output and input ports
            port->setPos(0.0, ypos);
        }
        ypos += dy;
        nport++;
    }
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
    setLabel( hyphenate(m_item->displayName()) );
    IView::update_appearance();
}

QString ConnectableView::hyphenate(const QString &name) const
{
    QRegExp capital_letter("[A-Z]");
    QRegExp number("[0-9]");
    int next_capital = capital_letter.indexIn(name, 1);
    int next_number = number.indexIn(name, 1);
    if (next_capital > 0 && next_capital < name.size() - 2) {
        int first_split_index = (next_number > 0 && next_number < next_capital)
                ? next_number
                : next_capital;
        QString result = name.left(first_split_index) + QString("\n")
                + name.right(name.size()-first_split_index);
        return result;
    }
    return name;
}
