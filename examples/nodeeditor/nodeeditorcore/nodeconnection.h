// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODECONNECTION_H
#define NODECONNECTION_H

//! Node editor: original code is taken from
//! http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
//! Copyright (c) 2012, STANISLAW ADASZEWSKI

#include <QGraphicsPathItem>

namespace NodeEditor {

class NodePort;

//! Elastic connection to connect two NodePorts together.

class NodeConnection : public QGraphicsPathItem {
public:
    NodeConnection(QGraphicsScene* scene);
    virtual ~NodeConnection();

    void setPos1(const QPointF& pos);
    void setPos2(const QPointF& pos);
    void setPort1(NodePort* port);
    void setPort2(NodePort* port);

    void updatePosFromPorts();
    void updatePath();

private:
    QPointF m_pos1;
    QPointF m_pos2;
    NodePort* m_port1{nullptr};
    NodePort* m_port2{nullptr};
};

} // namespace NodeEditor

#endif // NODECONNECTION_H
