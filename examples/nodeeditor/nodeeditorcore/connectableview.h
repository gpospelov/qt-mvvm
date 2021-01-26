// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_CONNECTABLEVIEW_H
#define NODEEDITORCORE_CONNECTABLEVIEW_H

#include <QGraphicsItem>
#include <memory>

namespace NodeEditor {

class ConnectableItem;
class NodeInputPort;
class NodeOutputPort;
class ConnectableItemController;
class NodeConnection;

//! Represents ConnectableItem on QGraphicsScene. Shown as a reactangle with rounded corners,
//! gradient, label, and set of input/output ports to connect.
//! In current design, ConnectableView can have only single output port and multiple input ports
//! of different type.

class ConnectableView : public QGraphicsItem {
public:
    ConnectableView(ConnectableItem* item);
    ~ConnectableView() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*) override;

    virtual void makeChildConnected(ConnectableView* childView);

    QList<NodeInputPort*> inputPorts() const;

    NodeOutputPort* outputPort() const;

    ConnectableItem* connectableItem() const;

    QList<NodeConnection*> inputConnections() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    template <typename T> QList<T*> ports() const;

    QColor color() const;
    QString label() const;
    void init_ports();

    QRectF m_rect;                    //!< Bounding rectangle.
    ConnectableItem* m_item{nullptr}; //!< Underlying item of this view.
    std::unique_ptr<ConnectableItemController> m_controller;
};

//! Return list of ports of required type.

template <typename T> QList<T*> ConnectableView::ports() const
{
    QList<T*> result;
    for (auto child : childItems())
        if (auto casted = dynamic_cast<T*>(child); casted)
            result.push_back(casted);
    return result;
}

} // namespace NodeEditor

#endif // NODEEDITORCORE_CONNECTABLEVIEW_H
