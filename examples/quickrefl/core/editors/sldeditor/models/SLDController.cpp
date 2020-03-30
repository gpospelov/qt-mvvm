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
#include "layeritems.h"
#include "materialitems.h"
#include "materialmodel.h"
#include "samplemodel.h"

#include "layerelementcontroller.h"
#include "layerelementitem.h"
#include "sldelementmodel.h"

#include <mvvm/model/compounditem.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/signals/modelmapper.h>

#include <iostream>

using namespace ModelView;

SLDController::SLDController(MaterialModel* material_model, SampleModel* sample_model,
                             SLDElementModel* sld_model, GraphicsScene* scene_item)
    : p_material_model(material_model), p_sample_model(sample_model), p_sld_model(sld_model),
      p_scene_item(scene_item)
{
    connectSLDElementModel();
    connectLayerModel();
    connectMaterialModel();
    buildSLD();
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

void SLDController::connectSLDElementModel()
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

void SLDController::disconnectSLDElementModel() const
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

    disconnectSLDElementModel();
    clearScene();

    if (p_sample_model->rootItem()->childrenCount() == 0)
        return;

    string_vec identifiers = getIdentifierVector(p_sample_model->rootItem()->children().at(0));
    buildLayerControllers(identifiers);
    updateToView();
    connectSLDElementModel();
}

//! Remove all the segments, handles and roughness view items in the scene
void SLDController::clearScene()
{
    if (!p_scene_item)
        return;
    if (!p_sld_model)
        return;

    for (int i = 0; i < layer_controllers.size(); ++i) {
        layer_controllers.at(i)->disconnectFormModel();
        layer_controllers.at(i)->unsetScene();
        layer_controllers.at(i)->deleteViewItems();
        delete layer_controllers.at(i);
    }
    layer_controllers.clear();
    p_sld_model->clear();
}

//! build the identifier vector
string_vec SLDController::getIdentifierVector(SessionItem* item)
{
    string_vec output;

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

//! Build and set up the layer controllers
void SLDController::buildLayerControllers(string_vec& identifiers)
{
    if (!p_scene_item)
        return;
    if (!p_sld_model)
        return;

    for (auto& identifier : identifiers) {
        auto layer_element_item = p_sld_model->addLayer();
        auto layer_element_controller = new LayerElementController(layer_element_item);
        layer_element_controller->autoPopulate();
        layer_element_controller->setScene(p_scene_item);
        layer_element_controller->connectToModel();
        layer_element_controller->setSampleItemId(identifier);
        layer_controllers.push_back(layer_element_controller);
    }

    for (int i = 0; i < layer_controllers.size() - 1; ++i) {
        layer_controllers.at(i)->setLayerBelow(layer_controllers.at(i + 1));
    }
}

//! Update the view items with the changes in the material or layer models
void SLDController::updateToView(SessionItem* item)
{
    for (auto layer_controller : layer_controllers) {
        if (!item || item->parent()->identifier() == layer_controller->sampleItemId()) {
            auto layer_item =
                dynamic_cast<LayerItem*>(p_sample_model->findItem(layer_controller->sampleItemId()));
            auto roughness_item = layer_item->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
            auto material_item = dynamic_cast<SLDMaterialItem*>(
                p_material_model->findItem(layer_item->property(LayerItem::P_MATERIAL)
                                             .value<ModelView::ExternalProperty>()
                                             .identifier()));

            layer_controller->layerElementItem()->setProperty(
                LayerElementItem::P_ROUGHNESS, roughness_item->property(RoughnessItem::P_SIGMA));
            layer_controller->layerElementItem()->setProperty(
                LayerElementItem::P_WIDTH, layer_item->property(LayerItem::P_THICKNESS).toDouble());

            if (material_item){
                layer_controller->layerElementItem()->setProperty(
                    LayerElementItem::P_HEIGHT,
                    material_item->property(SLDMaterialItem::P_SLD_REAL).toDouble() * 1e6);
                layer_controller->layerElementItem()->setProperty(
                    LayerElementItem::P_TOP_BRUSH_COLOR,
                    material_item->property(SLDMaterialItem::P_COLOR));
                layer_controller->layerElementItem()->setProperty(
                    LayerElementItem::P_SIDE_BRUSH_COLOR,
                    material_item->property(SLDMaterialItem::P_COLOR));
            }
        }
    }
}
//! Update the material and layer models from the view items
void SLDController::updateFromView(SessionItem* item) {}
