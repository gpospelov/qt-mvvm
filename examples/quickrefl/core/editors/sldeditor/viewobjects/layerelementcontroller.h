// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERELEMENTCONTROLLER_H
#define LAYERELEMENTCONTROLLER_H

#include <QObject>
#include <QPainterPath>
#include <vector>

#include "mvvm/plotting/sceneadapterinterface.h"

class LayerElementItem;
class GraphicsScene;

class HandleElementView;
class SegmentElementView;
class RoughnessElementView;

class LayerElementController : public QObject
{
    Q_OBJECT

public:
    LayerElementController(LayerElementItem* layer_view_item);
    LayerElementItem* layerElementItem() const;
    void connectToModel() const;
    void disconnectFormModel() const;

    void setScene(GraphicsScene* scene);
    GraphicsScene* scene() const;
    void unsetScene();

    void setSampleItemId(std::string indentifier);
    std::string sampleItemId() const;
    void unsetSampleItemId();

    // ##################################################################################
    // Signals for the sld controller
signals:
    void heightChanged(std::string id, double value) const;
    void widthChanged(std::string id, double value) const;
    void roughnessChanged(std::string id, double value) const;

private:
    ModelView::SceneAdapterInterface* getSceneAdapter() const;

    // ##################################################################################
    // Inter layer logic related
public:
    void setLayerAbove(LayerElementController* layer_view_controller);
    void setLayerBelow(LayerElementController* layer_view_controller);
    LayerElementController* layerAbove() const;
    LayerElementController* layerBelow() const;
    void unsetLayerAbove(bool silent = true);
    void unsetLayerBelow(bool silent = true);

    // ##################################################################################
    // Segment and handle related
public:
    void setSideSegment(SegmentElementView* segment_view);
    void setTopSegment(SegmentElementView* segment_view);
    SegmentElementView* sideSegment() const;
    SegmentElementView* topSegment() const;
    void unsetSideSegment();
    void unsetTopSegment();

    void segmentViewMoved(SegmentElementView* segment_view);

protected:
    void updateSideSegment() const;
    void updateTopSegment() const;
    QRectF sideSegmentRect() const;
    QRectF topSegmentRect() const;
    void putSegementsOnScene() const;
    void removeSegmentsFromScene() const;

public:
    void setSegmentHandles(HandleElementView* first_handle, HandleElementView* secondHandle);
    HandleElementView* firstSegmentHandle() const;
    HandleElementView* secondSegmentHandle() const;
    void unsetSegmentHandles();

    void handleViewMoved(HandleElementView* handle_view);

protected:
    void updateSegmentHandles() const;
    QRectF firstSegmentHandleRect() const;
    QRectF secondSegmentHandleRect() const;
    void putSegmentHandlesOnScene() const;
    void removeSegmentHandlesFromScene() const;

    // ##################################################################################
    // Roughness related
public:
    void setRoughness(RoughnessElementView* roughness_view);
    void setRoughnessHandles(HandleElementView* first_handle_view,
                             HandleElementView* second_handle_view);
    RoughnessElementView* roughness() const;
    HandleElementView* leftRoughnessHandle() const;
    HandleElementView* rightRoughnessHandle() const;
    void unsetRoughness();
    void unsetRoughnessHandles();
    void updateRoughness() const;

protected:
    QPainterPath leftRoughnessPath() const;
    QPainterPath rightRoughnessPath() const;
    QRectF leftRoughnessHandleRect() const;
    QRectF rightRoughnessHandleRect() const;
    void putRoughnessOnScene() const;
    void putRoughnessHandlesOnScene() const;
    void removeRoughnessFromScene() const;
    void removeRoughnessHandlesFromScene() const;

private:
    LayerElementItem* p_model_item;
    GraphicsScene* p_scene = nullptr;
    std::string m_sample_item_id;

    std::vector<SegmentElementView*> m_segment_views = {nullptr, nullptr};
    std::vector<HandleElementView*> m_handle_views = {nullptr, nullptr};
    std::vector<HandleElementView*> m_rough_handles_views = {nullptr, nullptr};
    RoughnessElementView* p_roughness_view = nullptr;

    LayerElementController* p_controller_above = nullptr;
    LayerElementController* p_controller_below = nullptr;
};

#endif
