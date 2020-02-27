// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MultiLayerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"
#include "DesignerScene.h"
#include "LayerView.h"
#include "SampleModel.h"
#include "item_constants.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <mvvm/model/sessionitem.h>

namespace
{
constexpr qreal width_multiplier = 1.15;
constexpr qreal multilayer_height = IView::basic_height;
constexpr qreal multilayer_width = IView::basic_width * width_multiplier;

constexpr QRectF defaultShape();
bool acceptsModel(const ModelView::SessionItem* item, const std::string& model_type);
} // namespace

MultiLayerView::MultiLayerView(QGraphicsItem* parent)
    : ILayerView(parent, DesignerHelper::MULTILAYER)
{
    setColor(QColor(Qt::blue));

    setRectangle(defaultShape());
    setAcceptHoverEvents(false);
    setAcceptDrops(true);
    connect(this, &MultiLayerView::childrenChanged, this, &MultiLayerView::updateGeometry);
    updateGeometry();
}

MultiLayerView::~MultiLayerView()
{
    // manually disconnecting the signal because of multiple inheritance
    disconnect(this, &MultiLayerView::childrenChanged, this, &MultiLayerView::updateGeometry);
}

void MultiLayerView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(m_color);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle()));
    painter->drawRect(getRectangle());
}

void MultiLayerView::addView(IView* childView)
{
    ILayerView* layer = dynamic_cast<ILayerView*>(childView);
    if (!layer) {
        Q_ASSERT(layer);
        return;
    }

    if (childItems().contains(layer))
        return;

    addNewLayer(layer, m_layers.size());
    updateGeometry();
}

void MultiLayerView::addNewLayer(ILayerView* layer, int row)
{
    m_layers.insert(row, layer);
    connect(layer, &ILayerView::heightChanged, this, &MultiLayerView::updateGeometry,
            Qt::UniqueConnection);
    connect(layer, &ILayerView::widthChanged, this, &MultiLayerView::updateGeometry,
            Qt::UniqueConnection);
    connect(layer, &ILayerView::aboutToBeDeleted, this, &MultiLayerView::onLayerAboutToBeDeleted,
            Qt::UniqueConnection);
    layer->setParentItem(this);
}

void MultiLayerView::onLayerAboutToBeDeleted()
{
    ILayerView* layer = qobject_cast<ILayerView*>(sender());
    Q_ASSERT(layer);
    removeLayer(layer);
}

void MultiLayerView::removeLayer(ILayerView* layer)
{
    Q_ASSERT(m_layers.contains(layer));
    m_layers.removeOne(layer);
    updateGeometry();
}

//! Updates geometry of MultiLayerView from current childs geometries.
void MultiLayerView::updateGeometry()
{
    updateHeight();
    updateWidth();
    alignChildren();
    update();
}

//! Returns index of drop area for given coordinate.
int MultiLayerView::getDropArea(QPointF pos)
{
    int area(-1);
    for (int i = 0; i < m_drop_areas.size(); ++i) {
        if (m_drop_areas.at(i).contains(pos)) {
            area = i;
            break;
        }
    }
    return area;
}

//! Returns drop area rectangle corresponding to given row
QRectF MultiLayerView::getDropAreaRectangle(int row)
{
    if (row >= 0 && row < m_drop_areas.size()) {
        return m_drop_areas[row];
    } else {
        return QRectF();
    }
}

//! Returns line representing interface
QLineF MultiLayerView::getInterfaceLine(int row) const
{
    if (row >= 0 && row < m_interfaces.size()) {
        return m_interfaces[row];
    } else {
        return QLineF();
    }
}

void MultiLayerView::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    if (!checkDragEvent(event))
        QGraphicsItem::dragMoveEvent(event);
}

void MultiLayerView::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    const DesignerMimeData* mimeData = checkDragEvent(event);
    DesignerScene* designerScene = dynamic_cast<DesignerScene*>(scene());
    if (!mimeData || !designerScene)
        return;
    designerScene->sendModelCommand([name = mimeData->getClassName(), pos = event->pos(),
                                     this](ModelView::SessionModel& model) {
        model.insertNewItem(name, getItem(), {"", getDropArea(pos)});
    });
}

const DesignerMimeData* MultiLayerView::checkDragEvent(QGraphicsSceneDragDropEvent* event)
{
    const DesignerMimeData* mimeData = qobject_cast<const DesignerMimeData*>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return nullptr;
    }
    int row = getDropArea(event->pos());
    event->setAccepted(mimeData->hasFormat("bornagain/widget")
                       && acceptsModel(getItem(), mimeData->getClassName()) && row != -1);
    return mimeData;
}

void MultiLayerView::update_appearance()
{
    updateGeometry();
    ILayerView::update_appearance();
}

//! Updates MultiLayer height, sets y-positions of children, defines new drop areas.
void MultiLayerView::updateHeight()
{
    // drop areas are rectangles covering the area of layer interfaces
    m_drop_areas.clear();
    m_interfaces.clear();

    qreal height =
        std::accumulate(m_layers.begin(), m_layers.end(), 0.0, [](qreal sum, ILayerView* child) {
            return sum + child->boundingRect().height();
        });
    height += multilayer_height;

    m_rect.setTop(-height / 2.0);
    m_rect.setHeight(height);

    emit heightChanged();
}

//! Updates MultiLayerView width, sets x-positions of children.
void MultiLayerView::updateWidth()
{
    qreal max_width = 0.0;
    for (ILayerView* layer : m_layers)
        if (layer->boundingRect().width() > max_width)
            max_width = layer->boundingRect().width();

    const qreal mlayer_width = max_width > 0 ? max_width * width_multiplier : multilayer_width;
    m_rect.setLeft(-mlayer_width / 2.0);
    m_rect.setWidth(mlayer_width);

    emit widthChanged();
}

void MultiLayerView::alignChildren()
{
    if (m_layers.empty()) {
        m_drop_areas.append(boundingRect());
        const qreal center_y = m_rect.center().y();
        m_interfaces.append({{m_rect.left(), center_y}, {m_rect.right(), center_y}});
        return;
    }

    qreal y_pos = m_rect.top() + multilayer_height / 2.0;
    for (ILayerView* layer : m_layers) {
        const qreal l_height = layer->boundingRect().height();
        layer->setPos({0.0, y_pos + l_height / 2.0});
        m_drop_areas.append(
            QRectF(m_rect.left(), y_pos - l_height / 2.0, m_rect.width(), l_height));
        m_interfaces.append({{m_rect.left(), y_pos}, {m_rect.right(), y_pos}});
        y_pos += l_height;
    }
    const qreal l_height = m_layers.back()->boundingRect().height();
    m_drop_areas.append(QRectF(m_rect.left(), y_pos - l_height / 2.0, m_rect.width(), l_height));
    m_interfaces.append({{m_rect.left(), y_pos}, {m_rect.right(), y_pos}});
}

namespace
{
constexpr QRectF defaultShape()
{
    return QRectF(-multilayer_width / 2.0, -multilayer_height / 2.0, multilayer_width,
                  multilayer_height);
}

bool acceptsModel(const ModelView::SessionItem* item, const std::string& model_type)
{
    // implement this function
    return false;
}
} // namespace
