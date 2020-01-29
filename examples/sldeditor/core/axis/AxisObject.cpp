// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "AxisObject.h"
#include "TicksView.h"
#include "ViewWidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QStyleOption>

#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

//! The constructor of AxisObject
AxisObject::AxisObject()
    : QGraphicsObject(), color(QColor("grey")), m_x_scale_factor(1.), m_y_scale_factor(-1.)
{
    setZValue(0);
}

//! The paint method for the axis items
void AxisObject::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    std::cout << "I am being painted" << std::endl;

    QRectF _view_port_size = scene()->sceneRect();

    double center_x = _view_port_size.width() / 2. + _view_port_size.x();
    double center_y = _view_port_size.height() / 2. + _view_port_size.y();

    double offset_x = 25.;
    double offset_y = 25.;
    double pen_thickness = 5.;

    std::vector<std::vector<double>> points{{center_x - _view_port_size.width() / 2. + offset_x,
                                             center_y - _view_port_size.height() / 2. + offset_y},
                                            {center_x + _view_port_size.width() / 2. - offset_x,
                                             center_y - _view_port_size.height() / 2. + offset_y},
                                            {center_x + _view_port_size.width() / 2. - offset_x,
                                             center_y + _view_port_size.height() / 2. - offset_y},
                                            {center_x - _view_port_size.width() / 2. + offset_x,
                                             center_y + _view_port_size.height() / 2. - offset_y}};

    painter->setPen(QPen(color, pen_thickness));
    painter->drawLine(points[0][0], points[0][1], points[1][0], points[1][1]);
    painter->drawLine(points[1][0], points[1][1], points[2][0], points[2][1]);
    painter->drawLine(points[2][0], points[2][1], points[3][0], points[3][1]);
    painter->drawLine(points[3][0], points[3][1], points[0][0], points[0][1]);

    auto ticks_x = TicksView(fromSceneToRealX(fromAxisToSceneX(points[0][0])),
                             fromSceneToRealX(fromAxisToSceneX(points[1][0])));
    auto ticks_y = TicksView(fromSceneToRealY(fromAxisToSceneY(points[1][1])),
                             fromSceneToRealY(fromAxisToSceneY(points[2][1])));

    QRectF scene_rect = getSceneRect();
    double y_factor = scene_rect.height() / _view_port_size.height();

    std::cout << "point info" << points[1][1] << " " << fromAxisToSceneY(points[1][1]) << " "
              << points[2][1] << " " << fromAxisToSceneY(points[2][1]) << std::endl;
    std::cout << "factor info" << y_factor << " " << scene_rect.y() << std::endl;
    std::cout << "tick info " << ticks_y.range << " " << ticks_y.minPoint << " " << ticks_y.maxPoint
              << " " << ticks_y.tickSpacing << std::endl;

    double tick_length_x = 10;
    double tick_length_y = 10;

    // x ticks
    for (double i = ticks_x.niceMin + ticks_x.tickSpacing; i < ticks_x.niceMax;
         i += ticks_x.tickSpacing) {

        painter->drawLine(fromSceneToAxisX(fromRealToSceneX(i)), points[0][1] + pen_thickness / 2.,
                          fromSceneToAxisX(fromRealToSceneX(i)), points[0][1] + tick_length_y);
        painter->drawLine(fromSceneToAxisX(fromRealToSceneX(i)), points[2][1] - pen_thickness / 2.,
                          fromSceneToAxisX(fromRealToSceneX(i)), points[2][1] - tick_length_y);

        std::ostringstream str;
        if (ticks_x.range > 999.) {
            str << std::scientific << std::setprecision(1) << i;
        } else if ((ticks_x.range <= 999.) & (ticks_x.range >= 0.1)) {
            str << std::fixed << std::setprecision(1) << i;
        } else {
            str << std::scientific << std::setprecision(3) << i;
        }

        auto text = QString::fromStdString(str.str());
        auto text_size = QFontMetrics(painter->font()).size(Qt::TextSingleLine, text);

        painter->drawText(fromSceneToAxisX(i) - text_size.width() / 2.,
                          points[0][1] + pen_thickness / 2. - text_size.height() / 2., text);

        painter->drawText(fromSceneToAxisX(i) - text_size.width() / 2.,
                          points[2][1] + pen_thickness + text_size.height() / 2., text);
    }

    // y ticks
    for (float i = ticks_y.niceMin + ticks_y.tickSpacing; i < ticks_y.niceMax;
         i += ticks_y.tickSpacing) {

        painter->drawLine(points[0][0] + pen_thickness / 2., fromSceneToAxisY(fromRealToSceneY(i)),
                          points[0][0] + tick_length_y, fromSceneToAxisY(fromRealToSceneY(i)));

        painter->drawLine(points[1][0] - pen_thickness / 2., fromSceneToAxisY(fromRealToSceneY(i)),
                          points[1][0] - tick_length_y, fromSceneToAxisY(fromRealToSceneY(i)));

        painter->rotate(-90);

        std::ostringstream str;
        if (ticks_y.range > 999.) {
            str << std::scientific << std::setprecision(1) << i;
        } else if ((ticks_y.range <= 999.) & (ticks_y.range >= 0.1)) {
            str << std::fixed << std::setprecision(1) << i;
        } else {
            str << std::scientific << std::setprecision(3) << i;
        }

        auto text = QString::fromStdString(str.str());
        auto text_size = QFontMetrics(painter->font()).size(Qt::TextSingleLine, text);

        painter->drawText(-(fromSceneToAxisY(fromRealToSceneY(i)) + text_size.width() / 2.),
                          points[0][0] + pen_thickness / 2. - text_size.height() / 2., text);

        painter->drawText(-(fromSceneToAxisY(fromRealToSceneY(i)) + text_size.width() / 2.),
                          points[1][0] + pen_thickness + text_size.height() / 2., text);

        painter->rotate(90);
    }
}

//! The shape of the whole view
QPainterPath AxisObject::shape() const
{
    QPainterPath path;
    path.addRect(scene()->sceneRect());
    return path;
}

//! The bounding rectangle
QRectF AxisObject::boundingRect() const
{
    return scene()->sceneRect();
}

//! Convertion from Scene to real coordinates of X
double AxisObject::fromSceneToRealX(double input_x) const
{
    return input_x * m_x_scale_factor;
}

//! Convertion from Scene to real coordinates of Y
double AxisObject::fromSceneToRealY(double input_y) const
{
    return input_y * m_y_scale_factor;
}

//! Convertion of real to Scene coordinates of X
double AxisObject::fromRealToSceneX(double input_x) const
{
    return input_x / m_x_scale_factor;
}

//! Convertion of real to Scene coordinates of Y
double AxisObject::fromRealToSceneY(double input_y) const
{
    return input_y / m_y_scale_factor;
}

//! Convertion of Scene to axis coordinates of X
double AxisObject::fromSceneToAxisX(double input_x) const
{
    QRectF _view_port_size = scene()->sceneRect();
    QRectF scene_rect = getSceneRect();
    double x_factor = scene_rect.width() / _view_port_size.width();
    return (input_x - scene_rect.x()) / x_factor;
}

//! Convertion of Scene to axis coordinates of Y
double AxisObject::fromSceneToAxisY(double input_y) const
{
    QRectF _view_port_size = scene()->sceneRect();
    QRectF scene_rect = getSceneRect();
    double y_factor = scene_rect.height() / _view_port_size.height();
    return (input_y - scene_rect.y()) / y_factor;
}

//! Convertion of axis to Scene coordinates of x
double AxisObject::fromAxisToSceneX(double input_x) const
{
    QRectF _view_port_size = scene()->sceneRect();
    QRectF scene_rect = getSceneRect();
    double x_factor = scene_rect.width() / _view_port_size.width();
    return input_x * x_factor + scene_rect.x();
}

//! Convertion of axis to Scene coordinates of y
double AxisObject::fromAxisToSceneY(double input_y) const
{
    QRectF _view_port_size = scene()->sceneRect();
    QRectF scene_rect = getSceneRect();
    double y_factor = scene_rect.height() / _view_port_size.height();
    return input_y * y_factor + scene_rect.y();
}

// Get the QRectF of the scene if possibles
QRectF AxisObject::getSceneRect() const
{
    ViewWidget* main_view = dynamic_cast<ViewWidget*>(scene()->views().last()->parent()->parent());

    if (!main_view)
        return QRectF(0, 0, 1, 1);

    return main_view->mapToScene(main_view->viewport()->geometry()).boundingRect();
}
