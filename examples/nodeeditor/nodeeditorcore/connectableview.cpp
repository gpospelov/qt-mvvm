// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "connectableview.h"
#include "sampleitems.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace {
const int round_par = 5;
}

namespace NodeEditor {

ConnectableView::ConnectableView(QGraphicsObject* parent) : QGraphicsObject(parent) {}

QRectF ConnectableView::boundingRect() const
{
    return m_rect;
}

void ConnectableView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus))
        painter->setPen(Qt::DashLine);

    painter->drawRoundedRect(boundingRect(), round_par, round_par);
}

//! Returns base color of this item.

QColor ConnectableView::color() const
{
    return m_item ? QColor(QString::fromStdString(m_item->namedColor())) : QColor(Qt::red);
}

} // namespace NodeEditor
