// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layerelementcontroller.h"

#include "GraphicsScene.h"
#include "layerelementitem.h"
#include "segmentelementview.h"

#include <mvvm/signals/itemmapper.h>
#include <stdexcept>

using namespace ModelView;

LayerElementController::LayerElementController(LayerElementItem* layer_view_item)
    : QObject(), p_model_item(layer_view_item)
{
}

//! Returns the pointer to the LayerElementItem in the model
LayerElementItem* LayerElementController::layerElementItem() const
{
    return p_model_item;
}

//! Connect to the set item
void LayerElementController::connectToModel() const
{
    auto on_property_change = [this](ModelView::SessionItem*, std::string property_name) {
        if (property_name == LayerElementItem::P_X_POS) {
            updateSideSegment();
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_HEIGHT) {
            updateSideSegment();
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_WIDTH) {
            updateSideSegment();
            updateTopSegment();
        }

        if (property_name == LayerElementItem::P_SIDE_THICKNESS) {
            updateSideSegment();
        }
        if (property_name == LayerElementItem::P_SIDE_PEN_WIDTH) {
            updateSideSegment();
        }
        if (property_name == LayerElementItem::P_SIDE_PEN_COLOR) {
            updateSideSegment();
        }
        if (property_name == LayerElementItem::P_SIDE_BRUSH_COLOR) {
            updateSideSegment();
        }

        if (property_name == LayerElementItem::P_TOP_THICKNESS) {
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_TOP_PEN_WIDTH) {
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_TOP_PEN_COLOR) {
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_TOP_BRUSH_COLOR) {
            updateTopSegment();
        }
    };

    layerElementItem()->mapper()->setOnPropertyChange(on_property_change, this);
}

//! Disconnect from the set item
void LayerElementController::disconnectFormModel() const
{
    layerElementItem()->mapper()->unsubscribe(this);
}

//! Set the scene
void LayerElementController::setScene(GraphicsScene* scene)
{
    p_scene = scene;

    putSegementsOnScene();
}

//! Return the current set scene
GraphicsScene* LayerElementController::scene() const
{
    return p_scene;
}

//! Set the scene
void LayerElementController::unsetScene()
{
    removeSegmentsFromScene();

    p_scene = nullptr;
}

//! Get the scene adapter to convert to axes
SceneAdapterInterface* LayerElementController::getSceneAdapter() const
{
    if (!p_scene)
        return nullptr;

    return p_scene->getSceneAdapter();
}

//! Set the layer above the current one in relation
void LayerElementController::setLayerAbove(LayerElementController* layer_view_controller)
{
    p_controller_above = layer_view_controller;

    if (!(layer_view_controller->layerBelow() == this))
        layer_view_controller->setLayerBelow(this);
}

//! Set the layer below the current one in relation
void LayerElementController::setLayerBelow(LayerElementController* layer_view_controller)
{
    p_controller_below = layer_view_controller;

    if (!(layer_view_controller->layerAbove() == this))
        layer_view_controller->setLayerAbove(this);
}

//! Return the layer above the current one in relation
LayerElementController* LayerElementController::layerAbove() const
{
    return p_controller_above;
}

//! Return the layer below the current one in relation
LayerElementController* LayerElementController::layerBelow() const
{
    return p_controller_below;
}

//! Unset the layer above the current one in relation
void LayerElementController::unsetLayerAbove(bool silent)
{
    if (!p_controller_above)
        return;

    if (silent)
        p_controller_above->unsetLayerBelow(false);

    p_controller_above = nullptr;
}

//! Unset the layer below the current one in relation
void LayerElementController::unsetLayerBelow(bool silent)
{
    if (!p_controller_below)
        return;

    if (silent)
        p_controller_below->unsetLayerAbove(false);

    p_controller_below = nullptr;
}

//! Set the side segment elements
void LayerElementController::setSideSegment(SegmentElementView* segment_view)
{
    m_segment_views[0] = segment_view;
    updateSideSegment();
}

//! Set the top segment elements
void LayerElementController::setTopSegment(SegmentElementView* segment_view)
{
    m_segment_views[1] = segment_view;
    updateTopSegment();
}

//! Return the side Segment view
SegmentElementView* LayerElementController::sideSegment() const
{
    return m_segment_views[0];
}

//! Return the top Segment view
SegmentElementView* LayerElementController::topSegment() const
{
    return m_segment_views[1];
}

//! Unset the side segment elements
void LayerElementController::unsetSideSegment()
{
    if (m_segment_views[0] && scene() && m_segment_views[0]->scene() == scene())
        scene()->removeItem(m_segment_views[0]);

    m_segment_views[0] = nullptr;
}

//! Unset the top segment elements
void LayerElementController::unsetTopSegment()
{
    if (m_segment_views[1] && scene() && m_segment_views[1]->scene() == scene())
        scene()->removeItem(m_segment_views[1]);

    m_segment_views[1] = nullptr;
}

void LayerElementController::updateSideSegment() const
{
    if (!m_segment_views[0])
        return;

    auto pen = QPen();
    pen.setColor(layerElementItem()->property(LayerElementItem::P_SIDE_PEN_COLOR).value<QColor>());
    pen.setWidthF(layerElementItem()->property(LayerElementItem::P_SIDE_PEN_WIDTH).toDouble());
    m_segment_views.at(0)->setPen(pen);

    auto brush = QBrush();
    brush.setColor(
        layerElementItem()->property(LayerElementItem::P_SIDE_BRUSH_COLOR).value<QColor>());
    m_segment_views.at(0)->setBrush(brush);

    m_segment_views.at(0)->setRectangle(sideSegmentRect());
}

void LayerElementController::updateTopSegment() const
{
    if (!m_segment_views[1])
        return;

    auto pen = QPen();
    pen.setColor(layerElementItem()->property(LayerElementItem::P_TOP_PEN_COLOR).value<QColor>());
    pen.setWidthF(layerElementItem()->property(LayerElementItem::P_TOP_PEN_WIDTH).toDouble());
    m_segment_views.at(1)->setPen(pen);

    auto brush = QBrush();
    brush.setColor(
        layerElementItem()->property(LayerElementItem::P_TOP_BRUSH_COLOR).value<QColor>());
    m_segment_views.at(1)->setBrush(brush);

    m_segment_views.at(1)->setRectangle(topSegmentRect());
}

//! Return the side segment rectangle
QRectF LayerElementController::sideSegmentRect() const
{
    double pos = layerElementItem()->property(LayerElementItem::P_X_POS).toDouble();
    double height = layerElementItem()->property(LayerElementItem::P_HEIGHT).toDouble();
    double thickness = layerElementItem()->property(LayerElementItem::P_SIDE_THICKNESS).toDouble();
    return QRectF(pos - thickness / 2., 0., thickness, height);
}

//! Return the top segment rectangle
QRectF LayerElementController::topSegmentRect() const
{
    double pos = layerElementItem()->property(LayerElementItem::P_X_POS).toDouble();
    double height = layerElementItem()->property(LayerElementItem::P_HEIGHT).toDouble();
    double width = layerElementItem()->property(LayerElementItem::P_WIDTH).toDouble();
    double thickness = layerElementItem()->property(LayerElementItem::P_TOP_THICKNESS).toDouble();
    return QRectF(pos, height - thickness / 2., width, thickness);
}

//! Put segments on scene
void LayerElementController::putSegementsOnScene() const
{
    if (!scene())
        return;

    for (auto segment_view : m_segment_views) {
        if (segment_view)
            scene()->addItem(segment_view);
    }
}

//! Remove the segments from the scene
void LayerElementController::removeSegmentsFromScene() const
{
    if (!scene())
        return;
    for (auto segment_view : m_segment_views) {
        if (segment_view && segment_view->scene() == scene())
            scene()->removeItem(segment_view);
    }
}
