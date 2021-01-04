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

namespace NodeEditor {

//! Base class representing input/output ports of connectable view.
//! Looks like round element attached to parent's bounding box. Input and output ports of the
//! same type can be connected together.

class NodePort : public QGraphicsPathItem {
public:
    NodePort(QGraphicsItem* parent, const QString& portType);

    QString portType() const;

    virtual bool isInput() const = 0;

    bool isOutput() const;

private:
    QString m_portType; //! Port type.
};

//! Represents input port of connectable view.

class NodeInputPort : public NodePort {
    using NodePort::NodePort;
    bool isInput() const override;
};

//! Represents output port of connectable view.

class NodeOutputPort : public NodePort {
    using NodePort::NodePort;
    bool isInput() const override;
};

} // namespace NodeEditor

#endif
