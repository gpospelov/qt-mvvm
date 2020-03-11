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

#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/sessionitem.h>
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

class SLDController
{
public:
    SLDController(MaterialModel* material_model, SampleModel* sample_model, SLDViewModel* sld_model, GraphicsScene* scene_item);
    void setScene(GraphicsScene* scene);

private:
    void connectSLDModel();
    void buildSLD();
    void clearScene();
    std::vector<std::string> getIdentifierVector(ModelView::SessionItem* item);
    std::vector<SegmentView*> buildTopSegments(std::vector<std::string> &identifiers);
    std::vector<SegmentView*> buildSideSegments(std::vector<std::string> &identifiers);
    std::vector<std::vector<HandleView*>> buildHandles(std::vector<std::string> &identifiers);
    std::vector<RoughnessView*> buildRoughnessBoxes(std::vector<std::string> &identifiers);

    void connectViewItem(std::vector<SegmentView*> top_segments, 
                         std::vector<std::vector<HandleView*>> handles,
                         std::vector<SegmentView*> side_segments,
                         std::vector<RoughnessView*> roughness_views);

    void drawViewItems(std::vector<SegmentView*> top_segments, 
                       std::vector<std::vector<HandleView*>> handles,
                       std::vector<SegmentView*> side_segments,
                       std::vector<RoughnessView*> roughness_views);

    void updateAll();
    

private:
    MaterialModel* p_material_model;
    SampleModel* p_sample_model;
    SLDViewModel* p_sld_model;
    GraphicsScene* p_scene_item;
};

#endif //  SLDCONTROLLER_H
