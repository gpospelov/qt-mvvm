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

#include <QGraphicsScene>
#include <QMap>
#include <QModelIndex>

namespace ModelView
{
    class SessionItem;
    class SessionModel;
}

class InstrumentModel;
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


//! Main class which represents SessionModel on graphics scene
class DesignerScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DesignerScene(QObject *parent = nullptr);
    virtual ~DesignerScene();

    void setSampleModel(SampleModel *sampleModel);
    void setSelectionModel(QItemSelectionModel *model, FilterPropertyProxy *proxy);

    SampleModel *getSampleModel() { return m_sampleModel; }

    IView* getViewForItem(const ModelView::SessionItem* item);

    NodeEditor *getNodeEditor() { return m_nodeEditor;}

    // slots:
    void onSceneSelectionChanged();
    void onSessionSelectionChanged(const QItemSelection &, const QItemSelection &);
    void resetScene();
    void updateScene();

    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsRemoved();

    void setLayerInterfaceLine(const QLineF &line=QLineF()) { m_layer_interface_line = line;
                                                              invalidate(); }

    void deleteSelectedItems();

    void onEstablishedConnection(NodeEditorConnection *); // to process signals from NodeEditor
    void removeConnection(NodeEditorConnection *);

    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void onSmartAlign();

signals:
    void selectionModeChangeRequest(int);

protected:
    void drawForeground(QPainter* painter, const QRectF& rect);
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    void addViewForItem(ModelView::SessionItem* item);
    void updateViews();
    void deleteViews(const QModelIndex & parentIndex);
    void alignViews();
    void removeItemViewFromScene(ModelView::SessionItem *item);
    bool isMultiLayerNearby(QGraphicsSceneDragDropEvent *event);
    void adjustSceneRect();
    bool isAcceptedByMultiLayer(const DesignerMimeData *mimeData, QGraphicsSceneDragDropEvent *event);
    bool isLayerDragged() const;

    SampleModel *m_sampleModel;
    QItemSelectionModel *m_selectionModel;
    FilterPropertyProxy *m_proxy;
    bool m_block_selection;

    QMap<const ModelView::SessionItem*, IView*> m_ItemToView;
    //!< Correspondance of model's item and scene's view

    QLineF m_layer_interface_line;
    //!< Foreground line representing appropriate interface during layer's movement

    SampleViewAligner *m_aligner;

    NodeEditor *m_nodeEditor;
};


#endif // DESIGNERSCENE_H

