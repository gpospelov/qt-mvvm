// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SEGMENTVIEW_H
#define SEGMENTVIEW_H

#include "HandleView.h"
#include "ViewObject.h"

class SegmentItem;

/*!
@class Segment
@brief The visual Segment element
*/

class SegmentView : public ViewObject
{
    Q_OBJECT

public:
    SegmentView(SegmentItem* item);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF getSceneRect() const;
    SegmentItem* segmentItem() const;

public:
    void addHandles(HandleView* left_handle, HandleView* right_handle);
    void moveHandles();
    void refreshFromHandles();

private:
    void connectHandles();
    void disconnectHandles();

public:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    SegmentItem* segment_item;
    QColor color;
    HandleView* _left_handle;
    HandleView* _right_handle;
};

#endif // SEGMENTVIEW_H
