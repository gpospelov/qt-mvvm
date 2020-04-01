// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef ROUGHNESSELEMENTVIEW_H
#define ROUGHNESSELEMENTVIEW_H

#include "elementview.h"

#include <QBrush>
#include <QPainterPath>
#include <QPen>


//! The roughness QGraphicsViewItem
class RoughnessElementView : public ElementView
{
public:
    RoughnessElementView();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void setLeftPath(QPainterPath left_path);
    void setRightPath(QPainterPath right_path);
    void setBrush(QBrush brush);
    void setPen(QPen pen);

protected:
    QPainterPath m_left_path;
    QPainterPath m_right_path;
    QBrush m_brush;
    QPen m_pen;
};

#endif // ROUGHNESSELEMENTVIEW_H
