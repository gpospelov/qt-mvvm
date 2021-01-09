// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEPORT_H
#define NODEPORT_H

//! Node editor: original code is taken from
//! http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
//! Copyright (c) 2012, STANISLAW ADASZEWSKI

#include <QGraphicsObject>
#include <QList>

namespace NodeEditor {

class NodeConnection;
class ConnectableView;

//! Base class representing input/output ports of connectable view.
//! Looks like round element attached to parent's bounding box. Input and output ports of the
//! same type can be connected together.

class NodePort : public QGraphicsPathItem {
public:
    NodePort(QGraphicsItem* parent, QString portType);
    virtual ~NodePort() override;

    QString portType() const;

    virtual bool isInput() const = 0;

    bool isOutput() const;

    virtual void initPort() = 0;

    void append(NodeConnection* connection);

    void remove(NodeConnection* connection);

    bool isConnectable(const NodePort* other) const;

    bool isConnected(const NodePort* other) const;

    ConnectableView* connectableView() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    QString m_portType; //! Port type.
    QGraphicsTextItem* m_label{nullptr};
    QList<NodeConnection*> m_connections;
};

//! Represents input port of connectable view.

class NodeInputPort : public NodePort {
public:
    using NodePort::NodePort;
    bool isInput() const override;
    void initPort() override;
};

//! Represents output port of connectable view.

class NodeOutputPort : public NodePort {
public:
    using NodePort::NodePort;
    bool isInput() const override;
    void initPort() override;
};

} // namespace NodeEditor

#endif
