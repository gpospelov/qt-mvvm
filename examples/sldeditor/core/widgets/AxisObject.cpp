// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "AxisObject.h"
#include "ViewWidget.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsSceneMouseEvent>

#include <iostream>


AxisObject::AxisObject() : QGraphicsObject() , color(QColor("grey"))
{
    setZValue(0);
}

void AxisObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    std::cout<<"I am being painted"<<std::endl;
    
    QRectF _view_port_size = scene()->sceneRect();

    double center_x = _view_port_size.width()/2. + _view_port_size.x();
    double center_y = _view_port_size.height()/2. + _view_port_size.y();

    std::vector<std::vector<double>> points;

    points.push_back(std::vector<double>{
        center_x - _view_port_size.width()/2.+25,
        center_y - _view_port_size.height()/2.+25
    });
    points.push_back(std::vector<double>{
        center_x + _view_port_size.width()/2.-25,
        center_y - _view_port_size.height()/2.+25
    });
    points.push_back(std::vector<double>{
        center_x + _view_port_size.width()/2.-25,
        center_y + _view_port_size.height()/2.-25
    });
    points.push_back(std::vector<double>{
        center_x - _view_port_size.width()/2.+25,
        center_y + _view_port_size.height()/2.-25
    });

    painter->setPen(QPen(color, 5. ));
    painter->drawLine(
        points[0][0],points[0][1],
        points[1][0],points[1][1]
    );
    painter->drawLine(
        points[1][0],points[1][1],
        points[2][0],points[2][1]
    );
    painter->drawLine(
        points[2][0],points[2][1],
        points[3][0],points[3][1]
    );
    painter->drawLine(
        points[3][0],points[3][1],
        points[0][0],points[0][1]
    );
    ViewWidget* main_view = dynamic_cast<ViewWidget*>(scene()->views().last()->parent()->parent());

    if (!main_view) 
        return;

    QRectF scene_rect = main_view->visibleRect();
    std::cout<<scene_rect.x()<<" "<<scene_rect.y()<<" "<<scene_rect.x()+scene_rect.width()<<" "<<scene_rect.y()+scene_rect.height()<<std::endl;

}

QPainterPath AxisObject::shape() const
{
    QPainterPath path;
    path.addRect(-10,-10,20,20);
    return path;
}

QRectF AxisObject::boundingRect() const
{
    return _view_port_size;
}

void AxisObject::refresh()
{
    update();

}

