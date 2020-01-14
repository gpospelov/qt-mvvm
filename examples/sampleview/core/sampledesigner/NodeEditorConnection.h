// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCONNECTION_H
#define NODEEDITORCONNECTION_H

/*
 * Node editor: original code is taken from
 * http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
 * Copyright (c) 2012, STANISLAW ADASZEWSKI
 */

#include "DesignerHelper.h"
#include <QGraphicsPathItem>

class NodeEditorPort;
class ConnectableView;

class NodeEditorConnection : public QGraphicsPathItem
{
public:
    NodeEditorConnection(QGraphicsScene* scene);
    ~NodeEditorConnection() override;

    void setPos1(const QPointF& p);
    void setPos2(const QPointF& p);
    void setPort1(NodeEditorPort* p);
    void setPort2(NodeEditorPort* p);
    void updatePosFromPorts();
    void updatePath();

    NodeEditorPort* port1() const;
    NodeEditorPort* port2() const;

    NodeEditorPort* inputPort();
    NodeEditorPort* outputPort();

    int type() const override { return DesignerHelper::NODE_EDITOR_CONNECTION; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    //! returns parent view, i.e. the view which owns input port of given connection
    ConnectableView* getParentView();

    //! returns child view, i.e. the view which owns output port of given connection
    ConnectableView* getChildView();

private:
    QPointF pos1;
    QPointF pos2;
    NodeEditorPort* m_port1;
    NodeEditorPort* m_port2;
};

#endif // NODEEDITORCONNECTION_H
