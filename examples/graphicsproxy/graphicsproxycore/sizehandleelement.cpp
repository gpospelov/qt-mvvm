// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sizehandleelement.h"
#include "regionofinterestview.h"
#include "mvvm/utils/containerutils.h"
#include <QCursor>
#include <QPainter>
#include <functional>
#include <map>
#include <stdexcept>

namespace GraphicsProxy {

namespace {

//! Constructs vector of all possible handle elements together with accompanying information.

auto create_handle_data()
{
    std::vector<SizeHandleElement::HandleInfo> result = {
        {SizeHandleElement::topleft, Qt::SizeFDiagCursor, SizeHandleElement::bottomright,
         [](auto r) { return r.topLeft(); }},
        {SizeHandleElement::topmiddle, Qt::SizeVerCursor, SizeHandleElement::bottommiddle,
         [](auto r) { return QPointF(r.x() + r.width() / 2., r.y()); }},
        {SizeHandleElement::topright, Qt::SizeBDiagCursor, SizeHandleElement::bottomleft,
         [](auto r) { return r.topRight(); }},
        {SizeHandleElement::middleright, Qt::SizeHorCursor, SizeHandleElement::middleleft,
         [](auto r) { return QPointF(r.x() + r.width(), r.y() + r.height() / 2.); }},
        {SizeHandleElement::bottomright, Qt::SizeFDiagCursor, SizeHandleElement::topleft,
         [](auto r) { return r.bottomRight(); }},
        {SizeHandleElement::bottommiddle, Qt::SizeVerCursor, SizeHandleElement::topmiddle,
         [](auto r) { return QPointF(r.x() + r.width() / 2., r.y() + r.height()); }},
        {SizeHandleElement::bottomleft, Qt::SizeBDiagCursor, SizeHandleElement::topright,
         [](auto r) { return r.bottomLeft(); }},
        {SizeHandleElement::middleleft, Qt::SizeHorCursor, SizeHandleElement::middleright,
         [](auto r) { return QPointF(r.x(), r.y() + r.height() / 2.); }}};

    return result;
}

} // namespace

SizeHandleElement::SizeHandleElement(SizeHandleElement::HandleInfo info, RegionOfInterestView* view)
    : QGraphicsItem(view), m_roiView(view), m_info(std::move(info))
{
    setCursor(QCursor(info.cursor));
    setVisible(false);
}

//! Factory method to create new SizeHandleElement for given position enum.

SizeHandleElement* SizeHandleElement::create(SizeHandleElement::EHandlePosition position,
                                             RegionOfInterestView* view)
{
    static auto handle_data = create_handle_data();
    auto info = std::find_if(handle_data.begin(), handle_data.end(),
                             [position](auto d) { return d.position == position; });
    if (info == handle_data.end())
        throw std::runtime_error("Error in SizeHandleElement: can't construct the data");

    return new SizeHandleElement(*info, view);
}

//! Returns vector of all possible handle positions;

std::vector<SizeHandleElement::EHandlePosition> SizeHandleElement::possible_handle_positions()
{
    static auto handle_data = create_handle_data();
    std::vector<SizeHandleElement::EHandlePosition> result;
    std::transform(handle_data.begin(), handle_data.end(), std::back_inserter(result),
                   [](auto x) { return x.position; });
    return result;
}

QRectF SizeHandleElement::boundingRect() const
{
    return QRectF(-4.0, -4.0, 8.0, 8.0);
}

//! Updates position of handle on reference rectangle.

void SizeHandleElement::updateHandleElementPosition(const QRectF& rect)
{
    setPos(m_info.rect_to_pos(rect));
}

//! Returns position identifier of this handle.

SizeHandleElement::EHandlePosition SizeHandleElement::handlePosition() const
{
    return m_info.position;
}

//! Returns position of identifier located at opposite "side" of rectangle.

SizeHandleElement::EHandlePosition SizeHandleElement::oppositeHandlePosition() const
{
    return m_info.opposite_position;
}

//! Returns true if this handle is one of the corners.

bool SizeHandleElement::isCornerHandle() const
{
    static std::vector<EHandlePosition> expected = {topleft, topright, bottomleft, bottomright};
    return ModelView::Utils::Contains(expected, m_info.position);
}

//! Returns true if this handle is intended for resize along y-direction only.

bool SizeHandleElement::isVerticalHandle() const
{
    static std::vector<EHandlePosition> expected = {topmiddle, bottommiddle};
    return ModelView::Utils::Contains(expected, m_info.position);
}

//! Returns true if this handle is intended for resize along x-direction only.

bool SizeHandleElement::isHorizontalHandle() const
{
    static std::vector<EHandlePosition> expected = {middleleft, middleright};
    return ModelView::Utils::Contains(expected, m_info.position);
}

void SizeHandleElement::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(226, 235, 244));

    painter->setBrush(brush);
    painter->setPen(QPen(QColor(99, 162, 217)));
    painter->drawRect(boundingRect());
}

void SizeHandleElement::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_roiView->setActiveHandle(this);
    QGraphicsItem::mousePressEvent(event);
}

void SizeHandleElement::mouseReleaseEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    // it is not triggered since we are in move mode, so have to do the same in RegionOfInterestView
    //    roi_view->setActiveHandle(nullptr);
    //    QGraphicsItem::mouseReleaseEvent(event);
}

} // namespace GraphicsProxy
