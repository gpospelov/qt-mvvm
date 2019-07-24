// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/NodeEditor.h
//! @brief     Defines class NodeEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef NODEEDITOR_H
#define NODEEDITOR_H

/*
 * Node editor: original code is taken from
 * http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
 * Copyright (c) 2012, STANISLAW ADASZEWSKI
 */

#include <QObject>

class QGraphicsScene;
class NodeEditorConnection;
class QGraphicsItem;
class QPointF;
class QGraphicsSceneMouseEvent;

//! The NodeEditor class implement for QGraphicsScene an editable schematic
//! of the dependency graph, displaying nodes and the connections between their
//! attributes
class NodeEditor : public QObject
{
	Q_OBJECT

public:
    explicit NodeEditor(QObject *parent = 0);

    void install(QGraphicsScene *scene);

    bool eventFilter(QObject *object, QEvent *event);

signals:
    void selectionModeChangeRequest(int);
    void connectionIsEstablished(NodeEditorConnection *);

private:
	QGraphicsItem *itemAt(const QPointF&);

private:
    bool processMousePress(QGraphicsSceneMouseEvent *event);
    bool processMouseMove(QGraphicsSceneMouseEvent *event);
    bool processMouseRelease(QGraphicsSceneMouseEvent *event);

    QGraphicsScene *m_scene;
    NodeEditorConnection *m_conn;
};

#endif // NODEEDITOR_H
