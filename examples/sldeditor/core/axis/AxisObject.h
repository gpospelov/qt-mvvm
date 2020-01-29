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
    AxisObject();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

public:
    AxisItem* axisItem() const;

    double fromSceneToRealX(double input_x) const;
    double fromSceneToRealY(double input_y) const;
    double fromRealToSceneX(double input_x) const;
    double fromRealToSceneY(double input_y) const;

    double fromSceneToAxisX(double input_x) const;
    double fromSceneToAxisY(double input_y) const;
    double fromAxisToSceneX(double input_x) const;
    double fromAxisToSceneY(double input_y) const;

private:
    QRectF getSceneRect() const;

private:
    QColor color;
    AxisItem* axis_item;
    double x_scale_factor;
    double y_scale_factor;
};

#endif // AXISOBJECT_H
