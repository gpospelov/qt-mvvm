// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_NODECONNECTION_H
#define NODEEDITORCORE_NODECONNECTION_H

//! Node editor: original code is taken from
//! http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
//! Copyright (c) 2012, STANISLAW ADASZEWSKI

#include <QGraphicsPathItem>

namespace NodeEditor {

class NodePort;
class ConnectableView;

//! Elastic connection to connect two NodeInput ports together.

class NodeConnection : public QGraphicsPathItem {
public:
    NodeConnection(QGraphicsScene* scene);
    virtual ~NodeConnection();

    void setPos1(const QPointF& pos);
    void setPos2(const QPointF& pos);
    void setPort1(NodePort* port);
    void setPort2(NodePort* port);

    void updatePath();

    NodePort* port1() const;

    bool hasPort(const NodePort *port) const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    ConnectableView* childView() const;

    ConnectableView* parentView() const;

private:
    QPointF m_pos1;
    QPointF m_pos2;
    NodePort* m_port1{nullptr}; //! The beginning of the connection.
    NodePort* m_port2{nullptr}; //! Connection end.
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_NODECONNECTION_H
