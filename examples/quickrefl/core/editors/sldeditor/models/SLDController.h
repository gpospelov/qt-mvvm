// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SLDCONTROLLER_H
#define SLDCONTROLLER_H

#include <QObject>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <vector>

class MaterialModel;
class SampleModel;
class SLDElementModel;
class GraphicsScene;
class LayerElementController;

/*!
@class SLDController
@brief This manages model connectivity
*/
using string_vec = std::vector<std::string>;
using layer_ctrl_vec = std::vector<LayerElementController*>;

class SLDController : public QObject
{
    Q_OBJECT

public:
    SLDController(MaterialModel* material_model, SampleModel* sample_model,
                  SLDElementModel* sld_model, GraphicsScene* scene_item);
    void setScene(GraphicsScene* scene);

private:
    void connectMaterialModel();
    void connectLayerModel();
    void connectSLDElementModel();
    void disconnectMaterialModel() const;
    void disconnectLayerModel() const;
    void disconnectSLDElementModel() const;

    void buildSLD();
    void clearScene();
    string_vec getIdentifierVector(ModelView::SessionItem* item);
    void buildLayerControllers(string_vec& identifiers);
    void connectLayerControllers();
    void disconnectLayerControllers();

    void updateToView(ModelView::SessionItem* item = nullptr);
    void updateThicknessFromView(std::string identifier, double value);
    void updateSLDFromView(std::string identifier, double value);
    void updateRoughnessFromView(std::string identifier, double value);

private:
    MaterialModel* p_material_model;
    SampleModel* p_sample_model;
    SLDElementModel* p_sld_model;
    GraphicsScene* p_scene_item;
    layer_ctrl_vec layer_controllers;
};

#endif //  SLDCONTROLLER_H
