// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SEGMENT_H
#define SEGMENT_H

#include <QGraphicsItem>
#include "Handle.h"

class SegmentItem;

/*!
@class Segment
@brief The visual Segment element
*/

class Segment : public QGraphicsObject
{
    
public:
    //! The constructor
    Segment(SegmentItem* item);

    //! The bounding rectangle of the handle
    QRectF boundingRect() const override;
    //! The shape ? 
    QPainterPath shape() const override;
    //! The overriden paint method
    void paint(
        QPainter* painter, const QStyleOptionGraphicsItem* option, 
        QWidget* widget) override;

    //! Retrieve segment item
    SegmentItem* segmentItem() const {return segment_item;};

    //! Add the handles at the end
    void addHandles(Handle* left_handle, Handle* right_handle);
    //! Move the linked handles
    void moveHandles();
    //! Refresh the properties from the handle info
    void refreshFromHandles();

private: 
    //! Connect the handles
    void connectHandles();
    //! Disconnect the handle signaling
    void disconnectHandles();

public:
    //! On move update the model
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    //! The link back to the item 
    SegmentItem* segment_item;
    //! The color property
    QColor color;
    //! placeholder for handles
    Handle* _left_handle;
    Handle* _right_handle;


};

#endif
