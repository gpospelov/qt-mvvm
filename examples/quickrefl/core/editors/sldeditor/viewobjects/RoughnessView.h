// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef ROUGHNESSVIEW_H
#define ROUGHNESSVIEW_H

#include "ViewObject.h"

class RoughnessViewItem;
class SegmentView;
class HandleView;
/*!
@class RoughnessView
@brief The visual Segment element
*/

class RoughnessView : public ViewObject
{
    Q_OBJECT

public:
    RoughnessView(RoughnessViewItem* item);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QPainterPath getPath() const;
    RoughnessViewItem* roughnessItem() const;

public:
    void moveHandles();
    void setSegments(SegmentView* left_segment_in, SegmentView* middle_segment_in,
                     SegmentView* right_segment_in);

private:
    void refreshFromSegments();
    void refreshFromLeftHandle();
    void refreshFromRightHandle();

    void connectSegments();
    void disconnectSegments();
    void connectHandles();
    void disconnectHandles();

private:
    RoughnessViewItem* roughness_item;

    SegmentView* left_segment;
    SegmentView* middle_segment;
    SegmentView* right_segment;

    HandleView* right_handle;
    HandleView* left_handle;
};

#endif // ROUGHNESSVIEW_H
