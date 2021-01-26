// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXYCORE_SIZEHANDLEELEMENT_H
#define GRAPHICSPROXYCORE_SIZEHANDLEELEMENT_H

#include <QGraphicsItem>
#include <vector>

namespace GraphicsProxy {

class RegionOfInterestView;

//! Handle element to resize RegionOfInterestView.

class SizeHandleElement : public QGraphicsItem {
public:
    //! This enum defines various handle positions which roi can have.

    enum EHandlePosition {
        topleft,
        topmiddle,
        topright,
        middleleft,
        middleright,
        bottomleft,
        bottommiddle,
        bottomright,
    };

    //! Aggregate to hold all handle's accompanying information.

    struct HandleInfo {
        SizeHandleElement::EHandlePosition position;          //! position of handle on rectangle
        Qt::CursorShape cursor;                               //! shape of cursor when hover on
        SizeHandleElement::EHandlePosition opposite_position; //! position of opposite corner
        //! calculates x,y of handle for given rectangle
        std::function<QPointF(const QRectF&)> rect_to_pos;
    };

    static SizeHandleElement* create(EHandlePosition position, RegionOfInterestView* view);

    static std::vector<EHandlePosition> possible_handle_positions();

    QRectF boundingRect() const override;

    void updateHandleElementPosition(const QRectF& rect);

    EHandlePosition handlePosition() const;

    EHandlePosition oppositeHandlePosition() const;

    bool isCornerHandle() const;
    bool isVerticalHandle() const;
    bool isHorizontalHandle() const;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    SizeHandleElement(HandleInfo info, RegionOfInterestView* view);

    RegionOfInterestView* m_roiView;
    HandleInfo m_info;
};

} // namespace GraphicsProxy

#endif // GRAPHICSPROXYCORE_SIZEHANDLEELEMENT_H
