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

//! Base class representing either input or output port of connectable view.
//! Looks like round element attached to parent's bounding box. Input and output ports of the
//! same type can be connected together.

class NodePort : public QGraphicsPathItem {
public:
    NodePort(QGraphicsItem* parent = nullptr);


    virtual bool isInput() = 0;
    virtual bool isOutput() = 0;



private:
   QString m_portType; //! Port type.
};

//! Represents input port of connectable view.

class NodeInputPort : public NodePort {
    using NodePort::NodePort;
    bool isInput() override;
    bool isOutput() override;
};

//! Represents output port of connectable view.

class NodeOutputPort : public NodePort {
    using NodePort::NodePort;
    bool isInput() override;
    bool isOutput() override;
};

} // namespace NodeEditor

#endif
