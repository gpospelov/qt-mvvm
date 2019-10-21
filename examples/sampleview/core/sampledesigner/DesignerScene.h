// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/DesignerScene.h
//! @brief     Defines class DesignerScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DESIGNERSCENE_H
#define DESIGNERSCENE_H

#include "SceneModelController.h"
#include <QGraphicsScene>
#include <QMap>
#include <memory>

namespace ModelView
{
    class SessionItem;
    class SessionModel;
}

class SampleModel;
class QItemSelectionModel;
class IView;
class QItemSelection;
class NodeEditorConnection;
class DesignerMimeData;
class SampleViewAligner;
class NodeEditor;
class FilterPropertyProxy;
class MaterialModel;
class SceneSelectionController;

//! Main class which represents SessionModel on graphics scene
class DesignerScene : public QGraphicsScene
{
    Q_OBJECT
public:
    using ModelCommand = std::function<void (ModelView::SessionModel& model)>;

    explicit DesignerScene(SampleModel* sample_model, QObject* parent = nullptr);
    ~DesignerScene() override;

    void setSelectionModel(QItemSelectionModel* model, FilterPropertyProxy*);

    IView* getViewForItem(ModelView::SessionItem* item) const;

    NodeEditor *getNodeEditor() { return m_nodeEditor;}
    SceneModelController& modelController() { return m_model_control; }

    // slots:
    void onModelChanged();
    void onModelDestroyed();

    void setLayerInterfaceLine(const QLineF &line=QLineF()) { m_layer_interface_line = line;
                                                              invalidate(); }

    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    void onSmartAlign();

    void sendModelCommand(SceneModelController::ModelCommand command);

signals:
    void selectionModeChangeRequest(int);

protected:
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);
    void drawForeground(QPainter* painter, const QRectF& rect) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void addViewForItem(ModelView::SessionItem* item);
    void resetScene();
    void updateScene();
    void updateViews();
    void alignViews();
    bool isMultiLayerNearby(QGraphicsSceneDragDropEvent *event);
    void adjustSceneRect();
    bool isAcceptedByMultiLayer(const DesignerMimeData *mimeData, QGraphicsSceneDragDropEvent *event);
    bool isLayerDragged() const;

    SceneModelController m_model_control;
    std::unique_ptr<SceneSelectionController> m_select_control;

    QMap<ModelView::SessionItem*, IView*> m_ItemToView;
    //!< Correspondance of model's item and scene's view

    QLineF m_layer_interface_line;
    //!< Foreground line representing appropriate interface during layer's movement

    SampleViewAligner *m_aligner;

    NodeEditor *m_nodeEditor;
};


#endif // DESIGNERSCENE_H

