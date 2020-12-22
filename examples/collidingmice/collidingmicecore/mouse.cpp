/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mouse.h"

#include "mousemodel.h"
#include "mvvm/signals/itemmapper.h"
#include "mvvm/utils/mathconstants.h"
#include "mvvm/utils/numericutils.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <cmath>

const qreal Pi = M_PI;
const qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

//! [0]
Mouse::Mouse(MouseItem* item)
    : mouseEyeDirection(0), color(item->property<QColor>(MouseItem::P_COLOR)), mouse_item(item)
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == MouseItem::P_XPOS)
            setX(mouse_item->property<double>(MouseItem::P_XPOS));
        if (property_name == MouseItem::P_YPOS)
            setY(mouse_item->property<double>(MouseItem::P_YPOS));
        if (property_name == MouseItem::P_COLOR)
            color = mouse_item->property<QColor>(MouseItem::P_COLOR);
        if (property_name == MouseItem::P_ANGLE) {
            qreal dx = std::sin(mouse_item->property<double>(MouseItem::P_ANGLE)) * 10;
            setRotation(rotation() + dx);
        }
    };
    mouse_item->mapper()->setOnPropertyChange(on_property_change, this);

    setPos(item->property<double>(MouseItem::P_XPOS), item->property<double>(MouseItem::P_YPOS));
    setRotation(ModelView::Utils::RandInt(0, 360 * 16));
}
//! [0]

//! [1]
QRectF Mouse::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}
//! [1]

//! [2]
QPainterPath Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}
//! [2]

//! [3]
void Mouse::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

    // Ears
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    painter->drawEllipse(-17, -12, 16, 16);
    painter->drawEllipse(1, -12, 16, 16);

    // Tail
    QPainterPath path(QPointF(0, 20));
    path.cubicTo(-5, 22, -5, 22, 0, 25);
    path.cubicTo(5, 27, 5, 32, 0, 30);
    path.cubicTo(-5, 32, -5, 42, 0, 35);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);
}
//! [3]

//! [4]
void Mouse::advance(int step)
{
    if (!step)
        return;
    //! [4]
    // Don't move too far away
    //! [5]

    qreal angle = mouse_item->property<double>(MouseItem::P_ANGLE);

    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        }
        else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    }
    else if (::sin(angle) < 0) {
        angle += 0.25;
    }
    else if (::sin(angle) > 0) {
        angle -= 0.25;
        //! [5] //! [6]
    }
    //! [6]

    // Try not to crash with any other mice
    //! [7]
    QList<QGraphicsItem*> dangerMice = scene()->items(
        QPolygonF() << mapToScene(0, 0) << mapToScene(-30, -50) << mapToScene(30, -50));
    foreach (QGraphicsItem* item, dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            angle += 0.5;
        }
        else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
            //! [7] //! [8]
        }
        //! [8] //! [9]
    }
    //! [9]

    // Add some random movement
    //! [10]
    if (dangerMice.size() > 1 && ModelView::Utils::RandInt(0, 10) == 0) {
        if (ModelView::Utils::RandInt(0, 1))
            angle += ModelView::Utils::RandDouble(0.0, 1 / 500.0);
        else
            angle -= ModelView::Utils::RandDouble(0.0, 1 / 500.0);
    }
    //! [10]

    //! [11]

    qreal speed = mouse_item->property<double>(MouseItem::P_SPEED);
    speed += (-50 + ModelView::Utils::RandInt(0, 100)) / 100.0;

    qreal dx = ::sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    auto new_coordinate = mapToParent(0, -(3 + sin(speed) * 3));
    mouse_item->setProperty(MouseItem::P_XPOS, new_coordinate.x());
    mouse_item->setProperty(MouseItem::P_YPOS, new_coordinate.y());
    mouse_item->setProperty(MouseItem::P_ANGLE, angle);
    mouse_item->setProperty(MouseItem::P_SPEED, speed);
}
//! [11]
