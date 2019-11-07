// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
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
    ConnectableView(QGraphicsItem* parent, int view_type, QRectF rect = QRectF(0, 0, 50, 50));
    ~ConnectableView() override;

    QRectF boundingRect() const override { return getRectangle(); }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    virtual QColor getColor() const { return m_color; }
    virtual QRectF getRectangle() const { return m_rect; }
    virtual void setRectangle(QRectF rect) { m_rect = rect; }
    virtual QString getLabel() const { return m_label; }
    virtual void setLabel(const QString& name);

    //! adds port to view
    virtual NodeEditorPort* addPort(const QString& name, NodeEditorPort::EPortDirection direction,
                                    NodeEditorPort::EPortType port_type);

    //! connects input port with given index with output port of other view
    void connectInputPort(ConnectableView* other, int port_number);

    QList<NodeEditorPort*> getInputPorts() { return m_input_ports; }
    QList<NodeEditorPort*> getOutputPorts() { return m_output_ports; }

    int getInputPortIndex(NodeEditorPort* port);

    void setColor(const QColor& color) { m_color = color; }

protected:
    void setPortCoordinates();
    virtual int getNumberOfPorts();
    virtual int getNumberOfOutputPorts();
    virtual int getNumberOfInputPorts();
    void update_appearance() override;

    QColor m_color;
    QRectF m_rect;
    int m_roundpar;
    double m_label_vspace; // vertical space occupied by the label
    QString m_label;
    QList<NodeEditorPort*> m_input_ports;
    QList<NodeEditorPort*> m_output_ports;

private:
    QString hyphenate(const QString& name) const;
};

#endif // CONNECTABLEVIEW_H
