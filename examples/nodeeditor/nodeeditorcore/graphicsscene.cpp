// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscene.h"
#include "connectableview.h"
#include "mvvm/model/itemutils.h"
#include "nodeconnection.h"
#include "nodecontroller.h"
#include "sampleitems.h"
#include "samplemodel.h"
#include "mvvm/model/modelutils.h"
#include <QDebug>

namespace {
const double scene_origin_x{0.0};
const double scene_origin_y{0.0};
const QRectF default_scene_rect{QPointF{scene_origin_x, scene_origin_y}, QSizeF{800, 600}};
} // namespace

namespace NodeEditor {

GraphicsScene::GraphicsScene(SampleModel* model, QObject* parent)
    : QGraphicsScene(parent), m_model(model), m_nodeController(new NodeController(this))
{
    setSceneRect(default_scene_rect);

    updateScene();

    connect(m_nodeController, &NodeController::connectionRequest, this,
            &GraphicsScene::onConnectionRequest);

    connect(this, &GraphicsScene::selectionChanged, this, &GraphicsScene::onSelectionChanged);
}

GraphicsScene::~GraphicsScene() = default;

//! Propagates elastic connection request between two views to the model.

void GraphicsScene::onConnectionRequest(ConnectableView* childView, ConnectableView* parentView)
{
    qDebug() << "on connection request";
    // On model level connection of views means simply changing the parent of underlying items.
    m_model->moveItem(childView->connectableItem(), parentView->connectableItem(), {"", -1});
}

//! Processes change in scene selection. Finds ConnectableItem corresponding to a selected view
//! and emit the signal.

void GraphicsScene::onSelectionChanged()
{
    auto selected = selectedViewItems<ConnectableView>();
    emit connectableItemSelectionChanged(selected.empty() ? nullptr
                                                          : selected.front()->connectableItem());
}

//! Disconnect items connected by the given connection.
//! All children items connected to the parents via this connection will be moved to the top of
//! the model (i.e. will become children of the model's root item). This in turn will trigger
//! corresponding ConnectableView recreation.

void GraphicsScene::deleteConnection(NodeConnection* connection)
{
    qDebug() << "deleteConnection 1.1";
    auto childView = connection->childView();
    m_model->moveItem(childView->connectableItem(), m_model->rootItem(), {"", -1});
    // No need to delete the connection explicitly.
    qDebug() << "deleteConnection 1.2";
}

//! Updates scene content from the model.

void GraphicsScene::updateScene()
{
    auto on_iterate = [this](auto item) {
        if (auto connectableItem = dynamic_cast<ConnectableItem*>(item); connectableItem)
            processItem(connectableItem);
    };
    ModelView::Utils::iterate(m_model->rootItem(), on_iterate);
}

//! Deletes all currently selected views on the scene. This propagates the request to delete to the
//! underlying model. Actual deletion of views will happen later, when the controller will be
//! notified about the model change.

void GraphicsScene::onDeleteSelectedRequest()
{
    qDebug() << "onDeleteSelectedRequest 1.1";
    // Delete explicitely selected connections.
    for (auto connection : selectedViewItems<NodeConnection>()) {
        qDebug() << "onDeleteSelectedRequest 1.1a";
        deleteConnection(connection);
        qDebug() << "onDeleteSelectedRequest 1.1b";
    }

    qDebug() << "onDeleteSelectedRequest 1.2";
    // Remove selected views.
    for (auto view : selectedViewItems<ConnectableView>()) {

//        // If the view has input connections, they have to be deleted first. This will lead in turn
//        // to moving of all connected children to the model's root item. As a result, they will all
//        // remain on the scene, while parent view will be deleted.
//        for (auto connection : view->inputConnections())
//            deleteConnection(connection);

//        // if the view has output connections, no action is required. View will be deleted,
//        // connections will be removed automatically, as soon as ports gone.

//        // deleting item
        ModelView::Utils::DeleteItemFromModel(view->connectableItem());
    }
    qDebug() << "onDeleteSelectedRequest 1.3";
}

//! Constructs a view for a given item and adds it to a scene, if necessary.
//! Connects new view with parent view.

void GraphicsScene::processItem(ConnectableItem* item)
{
    qDebug() << "processItem";

    auto itemView = findView(item);
    if (!itemView) {
        itemView = new ConnectableView(item);
        m_itemToView[item] = itemView;
        qDebug() << "adding item";
        addItem(itemView);
    }

    // If item has parent, look for corresponding view. Connect it with itemView.
    if (auto parentView = findView(dynamic_cast<ConnectableItem*>(item->parent())); parentView)
        parentView->makeChildConnected(itemView);
}

//! Find view for given item.

ConnectableView* GraphicsScene::findView(ConnectableItem* item)
{
    auto it = m_itemToView.find(item);
    return it == m_itemToView.end() ? nullptr : it->second;
}

//! Removes view corresponding to given item.

void GraphicsScene::removeViewForItem(ConnectableItem* item)
{
    qDebug() << "removeViewForItem 1.1" << QString::fromStdString(item->modelType()) << m_itemToView.size();
    auto it = m_itemToView.find(item);
    if (it != m_itemToView.end()) {
        qDebug() << "removeViewForItem 1.1a" << QString::fromStdString(item->modelType());
        delete it->second;
        m_itemToView.erase(it);
    }
    qDebug() << "removeViewForItem 1.2" << m_itemToView.size();
}

} // namespace NodeEditor
