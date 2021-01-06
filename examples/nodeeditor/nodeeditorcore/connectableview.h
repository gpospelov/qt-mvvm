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

#include <QGraphicsObject>

namespace NodeEditor {

class ConnectableItem;
class NodeInputPort;
class NodeOutputPort;

//! Represents ConnectableItem on QGraphicsScene. Shown as a reactangle with rounded corners,
//! gradient, label, and set of input/output ports to connect.
//! In current design, ConnectableView can have only single output port and multiple input ports
//! of different type.

class ConnectableView : public QGraphicsObject {
    Q_OBJECT

public:
    ConnectableView(ConnectableItem* item, QGraphicsObject* parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*) override;

    virtual void makeChildConnected(ConnectableView* childView);

    QList<NodeInputPort*> inputPorts() const;

    NodeOutputPort* outputPort() const;

private:
    template <typename T> QList<T*> ports() const;

    QColor color() const;
    QString label() const;
    void init_ports();

    QRectF m_rect;                    //!< Bounding rectangle.
    ConnectableItem* m_item{nullptr}; //!< Underlying item of this view.
};

template <typename T> QList<T*> ConnectableView::ports() const
{
    QList<T*> result;
    for (auto child : childItems())
        if (auto casted = dynamic_cast<T*>(child); casted)
            result.push_back(casted);
    return result;
}

} // namespace NodeEditor

#endif
