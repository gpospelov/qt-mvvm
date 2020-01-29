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

    double fromSceneToRealX(double input_x) const;
    double fromSceneToRealY(double input_y) const;
    double fromRealToSceneX(double input_x) const;
    double fromRealToSceneY(double input_y) const;

    double fromSceneToAxisX(double input_x) const;
    double fromSceneToAxisY(double input_y) const;
    double fromAxisToSceneX(double input_x) const;
    double fromAxisToSceneY(double input_y) const;

private:
    void getViewPortSize();
    QRectF getSceneRect() const;

private:
    //! The color property
    QColor color;
    //! The axis item linking all the info
    AxisItem* _axis_item;
    //! Scale items
    double m_x_scale_factor;
    double m_y_scale_factor;

};

#endif // AXISOBJECT_H
