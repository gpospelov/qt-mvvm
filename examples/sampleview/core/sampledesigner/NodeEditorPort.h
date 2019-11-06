// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORPORT_H
#define NODEEDITORPORT_H

/*
 * Node editor: original code is taken from
 * http://algoholic.eu/qnodeseditor-qt-nodesports-based-data-processing-flow-editor/
 * Copyright (c) 2012, STANISLAW ADASZEWSKI
 */

#include <QGraphicsPathItem>
#include <QString>
#include "DesignerHelper.h"

class NodeEditorConnection;
class IView;

class NodeEditorPort : public QGraphicsPathItem
{
public:
    enum { TYPE = DesignerHelper::NODE_EDITOR_PORT };

    //! type of ports, same type can be connected together
    enum EPortType { DEFAULT, INTERFERENCE, PARTICLE_LAYOUT, FORM_FACTOR, TRANSFORMATION };

    //! port direction
    enum EPortDirection { INPUT, OUTPUT };

    NodeEditorPort(QGraphicsItem *parent = 0, const QString &name = QString("unnamed"),
                   EPortDirection direction = INPUT, EPortType port_type = DEFAULT);

    virtual ~NodeEditorPort();

    bool isOutput();
    bool isInput();

    void remove(NodeEditorConnection *connection);
    void append(NodeEditorConnection *connection);

    const QString &portName() const;

    virtual int type() const;

    bool isConnected(NodeEditorPort *);

    bool isConnected();

    EPortType getPortType() const;

    static QColor getPortTypeColor(NodeEditorPort::EPortType port_type);

    void setLabel(QString name);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QString m_name;
    EPortDirection m_direction;
    EPortType m_port_type;
    QColor m_color;
    int m_radius;
    int m_margin;
    QVector<NodeEditorConnection *> m_connections;
    QGraphicsTextItem *m_label;
};

inline const QString &NodeEditorPort::portName() const
{
    return m_name;
}

inline int NodeEditorPort::type() const
{
    return TYPE;
}

inline bool NodeEditorPort::isConnected()
{
    return m_connections.size();
}

inline NodeEditorPort::EPortType NodeEditorPort::getPortType() const
{
    return m_port_type;
}

#endif // NODEEDITORPORT_H
