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
#include "mvvm/widgets/widgetutils.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace {
const int round_par = 5;

//! Returns vertical gradient using provided base color and rectangle.
QGradient view_gradient(const QColor& color, const QRectF& rect)
{
    QLinearGradient result(rect.x() + rect.width() / 2, rect.y(), rect.x() + rect.width() / 2,
                           rect.y() + rect.height());
    result.setColorAt(0, color);
    result.setColorAt(0.5, color.lighter(150));
    result.setColorAt(1, color);
    return result;
}

} // namespace

namespace NodeEditor {

ConnectableView::ConnectableView(ConnectableItem* item, QGraphicsObject* parent)
    : QGraphicsObject(parent), m_item(item)
{
    // make size of rectangle depending on 'M'-letter size to address scaling issues
    m_rect = QRectF(0, 0, ModelView::Utils::WidthOfLetterM() * 8,
                    ModelView::Utils::HeightOfLetterM() * 8);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF ConnectableView::boundingRect() const
{
    return m_rect;
}

void ConnectableView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(Qt::gray);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus))
        painter->setPen(Qt::DashLine);

    painter->setBrush(view_gradient(color(), boundingRect()));
    painter->drawRoundedRect(boundingRect(), round_par, round_par);
}

//! Returns base color of this item.

QColor ConnectableView::color() const
{
    return m_item ? QColor(QString::fromStdString(m_item->namedColor())) : QColor(Qt::red);
}

} // namespace NodeEditor
