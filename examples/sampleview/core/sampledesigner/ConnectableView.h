// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ConnectableView.h
//! @brief     Defines class ConnectableView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef CONNECTABLEVIEW_H
#define CONNECTABLEVIEW_H

#include "IView.h"
#include "NodeEditorPort.h"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class NodeEditorPort;

//! view of ISample's with rectangular shape and node functionality
class ConnectableView : public IView
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::ISAMPLE_RECT };
    ConnectableView(QGraphicsItem *parent = 0, QRectF rect = QRectF(0,0,50,50) );
    virtual ~ConnectableView(){}
    int type() const { return TYPE; }

    virtual QRectF boundingRect() const { return getRectangle(); }
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual QString getName() const { return m_name; }
    virtual QColor getColor() const { return m_color; }
    virtual QRectF getRectangle() const { return m_rect;}
    virtual void setRectangle(QRectF rect) { m_rect = rect; }
    virtual QString getLabel() const { return m_label; }
    virtual void setLabel(const QString &name);

    //! adds port to view
    virtual NodeEditorPort* addPort(const QString &name, NodeEditorPort::EPortDirection direction, NodeEditorPort::EPortType port_type);

    //! connects input port with given index with output port of other view
    void connectInputPort(ConnectableView *other, int port_number);

    QList<NodeEditorPort *> getInputPorts() { return m_input_ports; }
    QList<NodeEditorPort *> getOutputPorts() { return m_output_ports; }

    int getInputPortIndex(NodeEditorPort *port);

    virtual void setName(const QString &name) { m_name = name; }
    virtual void setColor(const QColor &color) { m_color = color; }

protected:
    virtual void setPortCoordinates();
    virtual int getNumberOfPorts();
    virtual int getNumberOfOutputPorts();
    virtual int getNumberOfInputPorts();
    virtual void update_appearance();

    QString m_name;
    QColor m_color;
    QRectF m_rect;
    int m_roundpar;
    double m_label_vspace; // vertical space occupied by the label
    QString m_label;
    QList<NodeEditorPort *> m_input_ports;
    QList<NodeEditorPort *> m_output_ports;

private:
    QString hyphenate(const QString& name) const;
};


//! default view of unimplemented ISample's
//class ISampleDefaultView : public ConnectableView
//{
//public:
//    ISampleDefaultView(QGraphicsItem *parent = 0) : ConnectableView(parent){}
//    //! сalls the ISampleViewVisitor's visit method
//};



#endif // CONNECTABLEVIEW_H
