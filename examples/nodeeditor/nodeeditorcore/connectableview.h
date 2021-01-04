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

//! Represents ConnectableItem on QGraphicsScene. Shown as a reactangle with rounded corners,
//! gradient, label, and set of input/output ports to connect.

class ConnectableView : public QGraphicsObject {
public:
    ConnectableView(ConnectableItem* item, QGraphicsObject* parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*) override;

    void makeChildConnected(ConnectableView* childView);

private:
    QColor color() const;
    QString label() const;
    void init_ports();

    QRectF m_rect;
    ConnectableItem* m_item{nullptr};
};

} // namespace NodeEditor

#endif
