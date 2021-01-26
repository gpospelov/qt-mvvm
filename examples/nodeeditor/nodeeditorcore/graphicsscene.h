// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_GRAPHICSSCENE_H
#define NODEEDITORCORE_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <map>

namespace NodeEditor {

class SampleModel;
class ConnectableView;
class ConnectableItem;
class NodeController;
class NodeConnection;
class GraphicsSceneController;

//! Custom graphics scene for node editor.
//! Listens for updates in SessionModel and populates the scene with views.
//! Contains the logic to establish and break connections between ConnectableViewItem.

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(SampleModel* model, QObject* parent);
    ~GraphicsScene() override;

    void updateScene();

    void onDeleteSelectedRequest();

signals:
    void connectableItemSelectionChanged(ConnectableItem* item);

protected:
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;

private slots:
    void onConnectionRequest(ConnectableView* childView, ConnectableView* parentView);
    void onSelectionChanged();

private:
    friend GraphicsSceneController;
    void processItem(ConnectableItem* item);
    ConnectableView* findView(ConnectableItem* item);
    void removeViewForItem(ConnectableItem* item);

    void disconnectConnectedViews(NodeConnection* connection);

    template <typename T> std::vector<T*> selectedViewItems();

    SampleModel* m_model{nullptr};
    std::map<ConnectableItem*, ConnectableView*> m_itemToView;
    NodeController* m_nodeController{nullptr};
};

template <typename T> inline std::vector<T*> GraphicsScene::selectedViewItems()
{
    std::vector<T*> result;
    for (auto item : selectedItems())
        if (auto casted = dynamic_cast<T*>(item); casted)
            result.push_back(casted);
    return result;
}

} // namespace NodeEditor

#endif // NODEEDITORCORE_GRAPHICSSCENE_H
