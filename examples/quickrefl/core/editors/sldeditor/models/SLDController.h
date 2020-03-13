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

#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <vector>

class MaterialModel;
class SampleModel;
class SLDViewModel;
class GraphicsScene;

class SegmentView;
class HandleView;
class RoughnessView;

/*!
@class SLDController
@brief This manages model connectivity
*/
using string_vec = std::vector<std::string>; 
using segment_vec = std::vector<SegmentView*>;
using handle_vec = std::vector<std::vector<HandleView*>>;
using roughness_vec = std::vector<RoughnessView*>;

class SLDController
{
public:
    SLDController(MaterialModel* material_model, SampleModel* sample_model, SLDViewModel* sld_model,
                  GraphicsScene* scene_item);
    void setScene(GraphicsScene* scene);

private:
    void connectMaterialModel();
    void connectLayerModel();
    void connectSLDModel();

    void disconnectMaterialModel() const;
    void disconnectLayerModel() const;
    void disconnectSLDModel() const;

    void buildSLD();
    void clearScene();
    string_vec getIdentifierVector(ModelView::SessionItem* item);
    segment_vec buildTopSegments(string_vec& identifiers);
    segment_vec buildSideSegments(string_vec& identifiers);
    handle_vec buildHandles(string_vec& identifiers);
    roughness_vec buildRoughnessBoxes(string_vec& identifiers);

    void connectViewItem(segment_vec top_segments,
                         handle_vec handles,
                         segment_vec side_segments,
                         roughness_vec roughness_views);

    void drawViewItems(segment_vec top_segments,
                       handle_vec handles,
                       segment_vec side_segments,
                       roughness_vec roughness_views);

    void updateToView(ModelView::SessionItem* item = nullptr);
    void updateFromView(ModelView::SessionItem* item = nullptr);

private:
    MaterialModel* p_material_model;
    SampleModel* p_sample_model;
    SLDViewModel* p_sld_model;
    GraphicsScene* p_scene_item;
};

#endif //  SLDCONTROLLER_H
