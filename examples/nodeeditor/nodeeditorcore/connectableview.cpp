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
#include "sceneutils.h"
#include "nodeport.h"
#include "mvvm/widgets/widgetutils.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace {
const int round_par = 5;

//! Returns rectangle to display ConnectableView label. Takes bounding box of a view as input
//! parameter.
QRectF label_rectangle(const QRectF& rect)
{
    return QRectF(rect.x(), rect.y(), rect.width(), rect.height() / 4);
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

    init_ports();
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

    painter->setBrush(CreateViewGradient(color(), boundingRect()));
    painter->drawRoundedRect(boundingRect(), round_par, round_par);

    painter->setPen(Qt::black);
    QFont serifFont("Monospace", 8, QFont::Normal);
    painter->setFont(serifFont);
    painter->drawText(label_rectangle(boundingRect()), Qt::AlignCenter, label());
}

//! Returns base color of this item.

QColor ConnectableView::color() const
{
    return m_item ? QColor(QString::fromStdString(m_item->namedColor())) : QColor(Qt::red);
}

//! Returns label of this item.

QString ConnectableView::label() const
{
    return m_item ? QString::fromStdString(m_item->displayName()) : QString("Unnamed");
}

//! Init ports to connect.

void ConnectableView::init_ports()
{
    auto port = new NodeInputPort(this, QString::fromStdString(m_item->modelType()));
    port->setPos(boundingRect().width(), boundingRect().height()*0.4);
}

} // namespace NodeEditor
