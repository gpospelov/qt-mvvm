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

//! Elastic connection to connect two NodePorts together.

class NodeConnection : public QGraphicsPathItem {
public:
    NodeConnection(QGraphicsScene* scene);
    virtual ~NodeConnection();
};

} // namespace NodeEditor

#endif // NODECONNECTION_H
