// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/NodeEditorConnection.h
//! @brief     Defines class NodeEditorConnection
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef NODEEDITORCONNECTION_H
#define NODEEDITORCONNECTION_H

/*
 * Node editor: original code is taken from
 * http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
 * Copyright (c) 2012, STANISLAW ADASZEWSKI
 */

#include <QGraphicsPathItem>
#include "DesignerHelper.h"

class NodeEditorPort;
class ConnectableView;

class NodeEditorConnection : public QGraphicsPathItem
{
public:
    enum { TYPE = DesignerHelper::NODE_EDITOR_CONNECTION };

    NodeEditorConnection(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~NodeEditorConnection();

    void setPos1(const QPointF &p);
    void setPos2(const QPointF &p);
    void setPort1(NodeEditorPort *p);
    void setPort2(NodeEditorPort *p);
    void updatePosFromPorts();
    void updatePath();

    NodeEditorPort* port1() const;
    NodeEditorPort* port2() const;

    NodeEditorPort *inputPort();
    NodeEditorPort *outputPort();

    int type() const { return TYPE; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! returns parent view, i.e. the view which owns input port of given connection
    ConnectableView *getParentView();

    //! returns child view, i.e. the view which owns output port of given connection
    ConnectableView *getChildView();

private:
    QPointF pos1;
    QPointF pos2;
    NodeEditorPort *m_port1;
    NodeEditorPort *m_port2;
};

#endif // NODEEDITORCONNECTION_H
