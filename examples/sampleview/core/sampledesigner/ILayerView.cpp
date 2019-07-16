// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ILayerView.cpp
//! @brief     Implements class ILayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ILayerView.h"
#include "DesignerHelper.h"
#include "DesignerScene.h"
#include "GUIHelpers.h"
#include "LayerItem.h"
#include "ExternalProperty.h"
#include "MultiLayerView.h"
#include "SampleModel.h"
#include "SessionItem.h"
#include <QGraphicsSceneMouseEvent>

QLineF MultiLayerCandidate::getInterfaceToScene()
{
    Q_ASSERT(multilayer);
    QLineF line = multilayer->getInterfaceLine(row);
    if(line.length() != 0) {
        QPointF p1(multilayer->mapToScene(line.p1()));
        QPointF p2(multilayer->mapToScene(line.p2()));
        const int prolongation = 20.0;
        return QLineF(p1.x() -prolongation, p1.y(), p2.x()+prolongation, p2.y());
    }

    return QLineF();
}

bool MultiLayerCandidate::operator<(const MultiLayerCandidate &cmp) const
{
    return cmp.distance < distance;
}

ILayerView::ILayerView(QGraphicsItem *parent) : ConnectableView(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

//! Propagates change of 'Thickness' dynamic property to screen thickness of ILayerView.
void ILayerView::onPropertyChange(const QString &propertyName)
{
    if (propertyName == LayerItem::P_THICKNESS) {
        updateHeight();
    } else if (propertyName == LayerItem::P_MATERIAL) {
        updateColor();
        updateLabel();
    }

    IView::onPropertyChange(propertyName);
}

void ILayerView::updateHeight()
{
    if(m_item->isTag(LayerItem::P_THICKNESS)) {
        m_rect.setHeight(DesignerHelper::nanometerToScreen(
            m_item->getItemValue(LayerItem::P_THICKNESS).toDouble()));
        setPortCoordinates();
        update();
        emit heightChanged();
    }
}

void ILayerView::updateColor()
{
    if(m_item->isTag(LayerItem::P_MATERIAL)) {
        QVariant v = m_item->getItemValue(LayerItem::P_MATERIAL);
        if (v.isValid()) {
            ExternalProperty mp = v.value<ExternalProperty>();
            setColor(mp.color());
            update();
        } else {
            Q_ASSERT(0);
        }
    }
}

void ILayerView::updateLabel()
{
    if(getInputPorts().size() < 1)
        return;

    NodeEditorPort *port = getInputPorts()[0];

    QString material = "" ;
    if(m_item->isTag(LayerItem::P_MATERIAL)){
        QVariant v = m_item->getItemValue(LayerItem::P_MATERIAL);
        if (v.isValid()) {
            ExternalProperty mp = v.value<ExternalProperty>();
            material = mp.text();
        }
    }

/* Thickness and roughness can be added, but the length of the string
 * becomes prohibitive.
    QString thickness = "" ;
    if(m_item->isTag(LayerItem::P_THICKNESS))
        thickness = m_item->getItemValue(LayerItem::P_THICKNESS).toString();

    QString roughness = "" ;
    if(m_item->isTag(LayerItem::P_ROUGHNESS)){
        QVariant x = m_item->getItemValue(LayerItem::P_ROUGHNESS);
        {...}
    }
*/
    QString infoToDisplay = material;
    port->setLabel(infoToDisplay);
}



//! Detects movement of the ILayerView and sends possible drop areas to GraphicsScene
//! for visualization.
QVariant ILayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {

        MultiLayerCandidate multilayerCandidate = getMultiLayerCandidate();
        if (multilayerCandidate) {
            DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
            designerScene->setLayerInterfaceLine(multilayerCandidate.getInterfaceToScene());
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void ILayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_drag_start_position = pos();
    }
    QGraphicsItem::mousePressEvent(event);
}

//! Detects possible MultiLayerView's to drop given ILayerView and propagate
//! request to SessionModel.
void ILayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
    Q_ASSERT(designerScene);
    designerScene->setLayerInterfaceLine(); // removing drop area hint from the scene

    if (QLineF(m_drag_start_position, pos()).length() == 0) {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    MultiLayerCandidate candidate = getMultiLayerCandidate();
    MultiLayerView *requested_parent = candidate.multilayer;
    int requested_row = candidate.row;

    // Simple move of single layer on the scene
    if (requested_parent == 0 && parentItem() == 0) {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved on top of MultiLayer but not in the right drop area:
    // returning layer back to starting position.
    if (requested_parent && requested_row == -1) {
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    SampleModel *model = designerScene->getSampleModel();

    // Layer was moved only slightly, to the same row of his own MultiLayer: returning back.
    if (requested_parent == parentItem()
        && requested_row == getItem()->parent()->getItems().indexOf(getItem())) {
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved from MultiLayer it belongs to, to an empty place of
    // the scene: changing ownership.
    if (parentItem() && !requested_parent) {
        QPointF newPos = mapToScene(event->pos()) - event->pos();
        this->getItem()->setItemValue(SessionGraphicsItem::P_XPOS, newPos.x());
        this->getItem()->setItemValue(SessionGraphicsItem::P_YPOS, newPos.y());

        model->moveItem(this->getItem(), 0);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved either from one MultiLayer to another, or is moved inside
    // one multilayer: changing ownership or row within same ownership.
    if (requested_parent) {
        model->moveItem(this->getItem(),
                                     requested_parent->getItem(), requested_row);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // throw only happens when not all cases were considered previously
    throw GUIHelpers::Error("LayerView::mouseReleaseEvent() -> Loggic error.");
}

void ILayerView::update_appearance()
{
    updateHeight();
    updateColor();
    updateLabel();
    ConnectableView::update_appearance();
}

//! Finds candidate (another MultiLayer) into which we will move our ILayerView.
//!
//! To become the candidate, the bounding rectangles of MultiLayerView and given
//! ILayerView should intersects and ILayerView center should be near appropriate
//! drop area. If more than one candidate is found, they will be sorted according
//! to the distance between drop area and ILayerVIew center
MultiLayerCandidate ILayerView::getMultiLayerCandidate()
{
    QVector<MultiLayerCandidate> candidates;

    QRectF layerRect = mapRectToScene(boundingRect());
    for(auto item : scene()->items()) {
        if (item->type() == DesignerHelper::MULTILAYER && item != this
            && !childItems().contains(item)) {
            MultiLayerView *multilayer = qgraphicsitem_cast<MultiLayerView *>(item);
            if (multilayer->mapRectToScene(multilayer->boundingRect()).intersects(layerRect)) {
                MultiLayerCandidate candidate;

                // calculate row number to drop ILayerView and distance to the nearest droping area
                int row = multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
                QRectF droparea = multilayer->mapRectToScene(multilayer->getDropAreaRectangle(row));
                int distance = std::abs(droparea.center().y() - layerRect.center().y());

                candidate.multilayer = multilayer;
                candidate.row = row;
                candidate.distance = distance;
                candidates.push_back(candidate);
            }
        }
    }
    // sorting MultiLayerView candidates to find one whose drop area is closer
    if (candidates.size()) {
        qSort(candidates.begin(), candidates.end());
        return candidates.back();
    }
    return MultiLayerCandidate();
}
