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
#include "handleelementview.h"
#include "layerelementitem.h"
#include "segmentelementview.h"

#include <mvvm/signals/itemmapper.h>
#include <stdexcept>
#include <string>

using namespace ModelView;

LayerElementController::LayerElementController(LayerElementItem* layer_view_item)
    : QObject(), p_model_item(layer_view_item), m_sample_item_id(" ")
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
    auto on_property_change = [this](ModelView::SessionItem* item, std::string property_name) {
        if (property_name == LayerElementItem::P_X_POS) {
            updateSideSegment();
            updateTopSegment();
            updateSegmentHandles();
        }
        if (property_name == LayerElementItem::P_HEIGHT) {
            emit heightChanged(m_sample_item_id,
                               layerElementItem()->property(LayerElementItem::P_HEIGHT).toDouble());
            updateSideSegment();
            updateTopSegment();
            updateSegmentHandles();
        }
        if (property_name == LayerElementItem::P_WIDTH) {
            emit widthChanged(m_sample_item_id,
                              layerElementItem()->property(LayerElementItem::P_WIDTH).toDouble());
            updateSideSegment();
            updateTopSegment();
            updateSegmentHandles();
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
    putSegmentHandlesOnScene();
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
    removeSegmentHandlesFromScene();

    p_scene = nullptr;
}

//! Set the idenfier of the sample item to report
void LayerElementController::setSampleItemId(std::string identifier)
{
    m_sample_item_id = identifier;
}

//! Return the set sample item identifier
std::string LayerElementController::sampleItemId() const
{
    return m_sample_item_id;
}

//! Unset the sample item identifier
void LayerElementController::unsetSampleItemId()
{
    m_sample_item_id = " ";
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

    double pos =
        p_controller_above->layerElementItem()->property(LayerElementItem::P_X_POS).toDouble()
        + p_controller_above->layerElementItem()->property(LayerElementItem::P_WIDTH).toDouble();
    layerElementItem()->setProperty(LayerElementItem::P_X_POS, pos);
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
    m_segment_views[0]->setLayerElementController(this);
    updateSideSegment();

    if (scene())
        scene()->addItem(m_segment_views[0]);
}

//! Set the top segment elements
void LayerElementController::setTopSegment(SegmentElementView* segment_view)
{
    m_segment_views[1] = segment_view;
    m_segment_views[1]->setLayerElementController(this);
    updateTopSegment();

    if (scene())
        scene()->addItem(m_segment_views[1]);
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

//! The move logic for the segments
void LayerElementController::segmentViewMoved(SegmentElementView* segment_view)
{
    if (segment_view == sideSegment()) {
        double x = sideSegment()->getLastPos().x();
        if (layerAbove()) {
            double w = 0;
            auto item = layerAbove()->layerElementItem();
            if (x < item->property(LayerElementItem::P_X_POS).toDouble()) {
                w = 1e-6;
                x = item->property(LayerElementItem::P_X_POS).toDouble() + w;
            } else {
                w = x - item->property(LayerElementItem::P_X_POS).toDouble();
            }
            item->setProperty(LayerElementItem::P_WIDTH, w);
        }
        layerElementItem()->setProperty(LayerElementItem::P_X_POS, x);
    } else if (segment_view == topSegment()) {
        double y = topSegment()->getLastPos().y();
        if (y < 0)
            y = 0;
        layerElementItem()->setProperty(LayerElementItem::P_HEIGHT, y);
    }
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

//! Set the side segment elements
void LayerElementController::setSegmentHandles(HandleElementView* first_handle,
                                               HandleElementView* second_handle)
{
    m_handle_views[0] = first_handle;
    m_handle_views[1] = second_handle;
    m_handle_views[0]->setLayerElementController(this);
    m_handle_views[1]->setLayerElementController(this);
    // updateSegmentHandles();

    if (scene()) {
        scene()->addItem(m_handle_views[0]);
        scene()->addItem(m_handle_views[1]);
    }
}

//! Return the side Segment view
HandleElementView* LayerElementController::firstSegmentHandle() const
{
    return m_handle_views[0];
}

//! Return the top Segment view
HandleElementView* LayerElementController::secondSegmentHandle() const
{
    return m_handle_views[1];
}

//! Unset the side segment elements
void LayerElementController::unsetSegmentHandles()
{
    if (m_handle_views[0] && scene() && m_handle_views[0]->scene() == scene())
        scene()->removeItem(m_handle_views[0]);
    if (m_handle_views[1] && scene() && m_handle_views[1]->scene() == scene())
        scene()->removeItem(m_handle_views[1]);

    m_handle_views[0] = nullptr;
    m_handle_views[1] = nullptr;
}

//! The move logic for the handles associated to the segments
void LayerElementController::handleViewMoved(HandleElementView* handle_view) {}

//! Update the handles of the segment
void LayerElementController::updateSegmentHandles() const
{
    auto pen = QPen();
    pen.setColor(
        layerElementItem()->property(LayerElementItem::P_HANDLE_PEN_COLOR).value<QColor>());
    pen.setWidthF(layerElementItem()->property(LayerElementItem::P_HANDLE_PEN_WIDTH).toDouble());

    auto brush = QBrush();
    brush.setColor(
        layerElementItem()->property(LayerElementItem::P_HANDLE_BRUSH_COLOR).value<QColor>());

    if (m_handle_views[0]) {
        m_handle_views.at(0)->setPen(pen);
        m_handle_views.at(0)->setBrush(brush);
        m_handle_views.at(0)->setRectangle(firstSegmentHandleRect());
    }
    if (m_handle_views[1]) {
        m_handle_views.at(1)->setPen(pen);
        m_handle_views.at(1)->setBrush(brush);
        m_handle_views.at(1)->setRectangle(secondSegmentHandleRect());
    }
}

//! Get the first segment handle rectangle
QRectF LayerElementController::firstSegmentHandleRect() const
{
    double pos = layerElementItem()->property(LayerElementItem::P_X_POS).toDouble();
    double radius = layerElementItem()->property(LayerElementItem::P_HANDLE_RADIUS).toDouble();
    return QRectF(pos - radius, -radius, 2 * radius, 2 * radius);
}

//! Get the second segment handle rectangle
QRectF LayerElementController::secondSegmentHandleRect() const
{
    double pos = layerElementItem()->property(LayerElementItem::P_X_POS).toDouble();
    double height = layerElementItem()->property(LayerElementItem::P_HEIGHT).toDouble();
    double radius = layerElementItem()->property(LayerElementItem::P_HANDLE_RADIUS).toDouble();
    return QRectF(pos - radius, height - radius, 2 * radius, 2 * radius);
}

//! Put the segment handles on the secene
void LayerElementController::putSegmentHandlesOnScene() const
{
    if (!scene())
        return;
    for (auto handle_view : m_handle_views) {
        if (handle_view)
            scene()->addItem(handle_view);
    }
}

//! Remove the segment handles on the scene
void LayerElementController::removeSegmentHandlesFromScene() const
{
    if (!scene())
        return;
    for (auto handle_view : m_handle_views) {
        if (handle_view && handle_view->scene() == scene())
            scene()->removeItem(handle_view);
    }
}
