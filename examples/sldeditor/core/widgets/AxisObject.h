// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef AXISOBJECT_H
#define AXISOBJECT_H

#include "AxisItem.h"

#include <QGraphicsObject>

/*!
@class AxisObject 
@brief This instance will manage all the axis visual components
*/

class AxisObject : public QGraphicsObject
{
    Q_OBJECT
public:
    //! The constructor
    AxisObject();

    //! The bounding rectangle of the handle
    QRectF boundingRect() const;
    //! The shape ? 
    QPainterPath shape() const;
    //! The overriden paint method
    void paint(
        QPainter* painter, const QStyleOptionGraphicsItem* option, 
        QWidget* widget);

public:
    //! Retrieve axis item
    AxisItem* axisItem() const {return _axis_item;};
    //! Refresh call after update of the viewport
    void refresh();

private:
    //! Reprocess boundaries internally
    void getViewPortSize();

private:
    //! The color property
    QColor color;
    //! The view rectangle in coordinates
    QRectF _view_port_size;
    //! The axis item linking all the info
    AxisItem* _axis_item;

};

#endif // AXISOBJECT_H
