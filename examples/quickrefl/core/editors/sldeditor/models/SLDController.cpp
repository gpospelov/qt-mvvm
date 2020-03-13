// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SLDController.h"
#include "GraphicsScene.h"
#include "SLDViewModel.h"
#include "layeritems.h"
#include "materialitems.h"
#include "materialmodel.h"
#include "samplemodel.h"

#include "HandleItem.h"
#include "HandleView.h"

#include "SegmentItem.h"
#include "SegmentView.h"

#include "RoughnessView.h"
#include "RoughnessViewItem.h"

#include <mvvm/model/compounditem.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/signals/modelmapper.h>

#include <iostream>

using namespace ModelView;

SLDController::SLDController(MaterialModel* material_model, SampleModel* sample_model,
                             SLDViewModel* sld_model, GraphicsScene* scene_item)
    : p_material_model(material_model), p_sample_model(sample_model), p_sld_model(sld_model),
      p_scene_item(scene_item)
{
    connectSLDModel();
    connectLayerModel();
    connectMaterialModel();
    buildSLD();
    updateToView();
}

//! Connect with signals of MaterialModel, SampleModel, SLDViewModel.
void SLDController::connectMaterialModel()
{
    auto on_mat_data_change = [this](SessionItem* item, int) { updateToView(item); };
    p_material_model->mapper()->setOnDataChange(on_mat_data_change, this);

    auto on_mat_model_destroyed = [this](SessionModel*) { p_material_model = nullptr; };
    p_material_model->mapper()->setOnModelDestroyed(on_mat_model_destroyed, this);
}

void SLDController::connectLayerModel()
{
    auto on_sam_data_change = [this](SessionItem* item, int) { updateToView(item); };
    p_sample_model->mapper()->setOnDataChange(on_sam_data_change, this);

    auto on_sam_item_inserted = [this](SessionItem*, TagRow) { buildSLD(); };
    p_sample_model->mapper()->setOnItemInserted(on_sam_item_inserted, this);

    auto on_sam_item_removed = [this](SessionItem*, TagRow) { buildSLD(); };
    p_sample_model->mapper()->setOnItemRemoved(on_sam_item_removed, this);

    auto on_sam_model_destroyed = [this](SessionModel*) { p_sample_model = nullptr; };
    p_sample_model->mapper()->setOnModelDestroyed(on_sam_model_destroyed, this);
}

void SLDController::connectSLDModel()
{
    auto on_sld_model_destroyed = [this](SessionModel*) { p_sld_model = nullptr; };
    p_sld_model->mapper()->setOnModelDestroyed(on_sld_model_destroyed, this);

    auto on_sld_data_change = [this](SessionItem* item, int) { updateFromView(item); };
    p_sld_model->mapper()->setOnDataChange(on_sld_data_change, this);
}

void SLDController::disconnectMaterialModel() const
{
    p_material_model->mapper()->unsubscribe(this);
}

void SLDController::disconnectLayerModel() const
{
    p_sample_model->mapper()->unsubscribe(this);
}

void SLDController::disconnectSLDModel() const
{
    p_sld_model->mapper()->unsubscribe(this);
}

void SLDController::setScene(GraphicsScene* scene)
{
    p_scene_item = scene;
    buildSLD();
}

//! Updates all material properties in LayerItems to get new material colors and labels.
void SLDController::buildSLD()
{
    if (!p_sld_model)
        return;
    if (!p_sample_model)
        return;
    if (!p_material_model)
        return;
    if (!p_scene_item)
        return;

    disconnectSLDModel();
    p_sld_model->clear();
    clearScene();

    if (p_sample_model->rootItem()->childrenCount() == 0)
        return;

    std::vector<std::string> identifiers =
        getIdentifierVector(p_sample_model->rootItem()->children().at(0));

    auto top_segments = buildTopSegments(identifiers);
    auto side_segments = buildSideSegments(identifiers);
    auto handles = buildHandles(identifiers);
    auto roughness = buildRoughnessBoxes(identifiers);

    connectViewItem(top_segments, handles, side_segments, roughness);
    drawViewItems(top_segments, handles, side_segments, roughness);
    updateToView();
    connectSLDModel();
}

void SLDController::clearScene()
{
    if (!p_scene_item)
        return;
    if (!p_sld_model)
        return;

    QList<QGraphicsItem*> items = p_scene_item->items();
    for (int i = 0; i < items.size(); ++i) {
        if (dynamic_cast<SegmentView*>(items[i])) {
            SegmentView* item = dynamic_cast<SegmentView*>(items[i]);
            item->setVisible(false);
            p_scene_item->removeItem(item);
            item->deleteLater();
        } else if (dynamic_cast<HandleView*>(items[i])) {
            HandleView* item = dynamic_cast<HandleView*>(items[i]);
            item->setVisible(false);
            p_scene_item->removeItem(item);
            item->deleteLater();
        } else if (dynamic_cast<RoughnessView*>(items[i])) {
            RoughnessView* item = dynamic_cast<RoughnessView*>(items[i]);
            item->setVisible(false);
            p_scene_item->removeItem(item);
            item->deleteLater();
        }
    }
}

std::vector<std::string> SLDController::getIdentifierVector(SessionItem* item)
{
    std::vector<std::string> output;

    auto children = item->children();
    for (int i = 0; i < item->childrenCount(); ++i) {
        if (dynamic_cast<MultiLayerItem*>(children.at(i))) {
            auto child = dynamic_cast<MultiLayerItem*>(children.at(i));
            for (int j = 0; j < child->property(MultiLayerItem::P_NREPETITIONS).toInt(); ++j) {
                auto child_output = getIdentifierVector(child);
                output.insert(output.end(), child_output.begin(), child_output.end());
            }
        } else if (dynamic_cast<LayerItem*>(children.at(i))) {
            auto child = dynamic_cast<LayerItem*>(children.at(i));
            output.push_back(child->identifier());
        }
    }
    return output;
}

std::vector<SegmentView*> SLDController::buildTopSegments(std::vector<std::string>& identifiers)
{
    std::vector<SegmentView*> output;
    for (const auto identifier : identifiers) {
        SegmentItem* segment_item = p_sld_model->addSegment(identifier);
        SegmentView* segment = new SegmentView(segment_item);
        output.push_back(segment);
    }
    return output;
}

std::vector<SegmentView*> SLDController::buildSideSegments(std::vector<std::string>& identifiers)
{
    std::vector<SegmentView*> output;
    for (int i = 1; i < identifiers.size(); ++i) {
        SegmentItem* segment_item = p_sld_model->addSegment("");
        SegmentView* segment = new SegmentView(segment_item);
        segment->segmentItem()->setProperty(SegmentItem::P_HORIZONTAL, false);
        segment->segmentItem()->setProperty(SegmentItem::P_WIDTH, 10.);
        output.push_back(segment);
    }
    return output;
}

std::vector<std::vector<HandleView*>>
SLDController::buildHandles(std::vector<std::string>& identifiers)
{
    std::vector<std::vector<HandleView*>> output;
    for (const auto identifier : identifiers) {
        HandleItem* handle_item_left = p_sld_model->addHandle();
        HandleItem* handle_item_right = p_sld_model->addHandle();
        HandleView* handle_left = new HandleView(handle_item_left);
        HandleView* handle_right = new HandleView(handle_item_right);
        output.push_back(std::vector<HandleView*>{handle_left, handle_right});
    }
    return output;
}

std::vector<RoughnessView*>
SLDController::buildRoughnessBoxes(std::vector<std::string>& identifiers)
{
    std::vector<RoughnessView*> output;
    for (int i = 1; i < identifiers.size(); ++i) {
        RoughnessViewItem* roughness_item = p_sld_model->addRoughness(identifiers[i]);
        RoughnessView* roughness_view = new RoughnessView(roughness_item);
        output.push_back(roughness_view);
    }
    return output;
}

void SLDController::connectViewItem(std::vector<SegmentView*> top_segments,
                                    std::vector<std::vector<HandleView*>> handles,
                                    std::vector<SegmentView*> side_segments,
                                    std::vector<RoughnessView*> roughness_views)
{

    for (int i = 0; i < top_segments.size(); ++i) {
        top_segments[i]->addHandles(handles[i][0], handles[i][1]);
    }

    for (int i = 1; i < top_segments.size(); ++i) {
        side_segments[i - 1]->addHandles(handles[i - 1][1], handles[i][0]);
    }

    for (int i = 1; i < top_segments.size(); ++i) {
        roughness_views[i - 1]->setSegments(top_segments[i - 1], side_segments[i - 1],
                                            top_segments[i]);
    }
}

void SLDController::drawViewItems(std::vector<SegmentView*> top_segments,
                                  std::vector<std::vector<HandleView*>> handles,
                                  std::vector<SegmentView*> side_segments,
                                  std::vector<RoughnessView*> roughness_views)
{
    if (!p_scene_item)
        return;

    for (auto* segment_view : top_segments) {
        p_scene_item->addItem(segment_view);
    }
    for (auto& handle_view : handles) {
        p_scene_item->addItem(handle_view.at(0));
        p_scene_item->addItem(handle_view.at(1));
    }
    for (auto* segment_view : side_segments) {
        p_scene_item->addItem(segment_view);
    }
    for (auto* roughness_view : roughness_views) {
        p_scene_item->addItem(roughness_view);
    }
}

void SLDController::updateToView(SessionItem* item)
{
    auto view_items = p_sld_model->rootItem()->children();
    if (!item) {
        for (auto* item : view_items) {
            if (dynamic_cast<SegmentItem*>(item)) {
                auto mod_item = dynamic_cast<SegmentItem*>(item);
                mod_item->fetchFromLayer(p_sample_model, p_material_model);
            } else if (dynamic_cast<RoughnessViewItem*>(item)) {
                auto mod_item = dynamic_cast<RoughnessViewItem*>(item);
                mod_item->fetchFromLayer(p_sample_model, p_material_model);
            }
        }
    } else {
        if (dynamic_cast<MultiLayerItem*>(item->parent())){
            buildSLD();
            return;
        }else{
            for (auto* item : view_items) {
                if (dynamic_cast<SegmentItem*>(item)) {
                    auto mod_item = dynamic_cast<SegmentItem*>(item);
                    mod_item->fetchFromLayer(p_sample_model, p_material_model);
                } else if (dynamic_cast<RoughnessViewItem*>(item)) {
                    auto mod_item = dynamic_cast<RoughnessViewItem*>(item);
                    mod_item->fetchFromLayer(p_sample_model, p_material_model);
                }
            }
        }
    }
    
}

void SLDController::updateFromView(SessionItem* item)
{

    if (dynamic_cast<SegmentItem*>(item->parent())) {
        auto segment_item = dynamic_cast<SegmentItem*>(item->parent());
        auto layer_item_session = p_sample_model->findItem(segment_item->layerIdentifier());
        if (!layer_item_session)
            return;

        if (segment_item->tagOfItem(item) == SegmentItem::P_WIDTH) {
            auto layer_item = dynamic_cast<LayerItem*>(layer_item_session);
            layer_item->setProperty(LayerItem::P_THICKNESS,
                                    segment_item->property(SegmentItem::P_WIDTH).toDouble());
        } else if (segment_item->tagOfItem(item) == SegmentItem::P_Y_POS) {
            auto layer_item = dynamic_cast<LayerItem*>(layer_item_session);
            auto material_item = dynamic_cast<SLDMaterialItem*>(
                p_material_model->findItem(layer_item->property(LayerItem::P_MATERIAL)
                                               .value<ModelView::ExternalProperty>()
                                               .identifier()));
            if (!material_item)
                return;
            material_item->setProperty(SLDMaterialItem::P_SLD_REAL,
                                       segment_item->property(SegmentItem::P_Y_POS).toDouble()
                                           * 1e-6);
        } else {
            return;
        }

    } else if (dynamic_cast<RoughnessViewItem*>(item->parent())) {
        auto roughness_view_item = dynamic_cast<RoughnessViewItem*>(item->parent());
        auto layer_item_session = p_sample_model->findItem(roughness_view_item->layerIdentifier());
        if (!layer_item_session)
            return;

        if (item->parent()->tagOfItem(item) == RoughnessViewItem::P_ROUGHNESS) {
            auto layer_item = dynamic_cast<LayerItem*>(layer_item_session);
            auto roughness_item = layer_item->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
            roughness_item->setProperty(
                RoughnessItem::P_SIGMA,
                roughness_view_item->property(RoughnessViewItem::P_ROUGHNESS).toDouble());
        } else {
            return;
        }
    }
}
