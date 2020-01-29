// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef VIEWOBJECT_H
#define VIEWOBJECT_H

#include "AxisObject.h"

#include <QGraphicsObject>

class ViewObject : public QGraphicsObject
{
    Q_OBJECT
public:
    
    ViewObject();
    QRectF boundingRect() const = 0;
    QPainterPath shape() const = 0;
    void paint(
            QPainter* painter, const QStyleOptionGraphicsItem* option, 
            QWidget* widget) = 0;
    AxisObject* getAxes() const;

};

#endif // VIEWOBJECT_H
