// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SEGMENTELEMENTVIEW_H
#define SEGMENTELEMENTVIEW_H

#include "elementview.h"

#include <QBrush>
#include <QPen>
#include <QRectF>

class LayerElementController;

//! The segment QGraphicsViewItem on the Graphicsscene
class SegmentElementView : public ElementView
{
public:
    SegmentElementView();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void setLayerElementController(LayerElementController* controller);
    void setRectangle(QRectF rectangle);
    void setBrush(QBrush brush);
    void setPen(QPen pen);
    QPointF getLastPos() const;

public:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

protected:
    LayerElementController* p_controller;
    QPointF m_pos;
    QRectF m_rectangle;
    QBrush m_brush;
    QPen m_pen;
};

#endif // SEGMENTVIEW_H
