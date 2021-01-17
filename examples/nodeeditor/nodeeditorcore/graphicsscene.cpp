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
#include "nodeconnection.h"
#include "nodecontroller.h"
#include "pieceslist.h"
#include "sampleitems.h"
#include "samplemodel.h"
#include "sceneutils.h"
#include "nodeport.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

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

void GraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->hasFormat(PiecesList::piecesMimeType()))
        event->accept();
    else
        event->ignore();
}

void GraphicsScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    // for later coordinate calculation, where to drop
    static QRectF refViewRectangle = ConnectableViewRectangle();

    auto mimeData = event->mimeData();
    if (!mimeData->hasFormat(PiecesList::piecesMimeType()))
        return;

    auto requestedTypes =
        ModelView::Utils::deserialize(mimeData->data(PiecesList::piecesMimeType()));

    for (const auto& itemType : requestedTypes) {
        QPointF dropPos(event->scenePos().x() - refViewRectangle.width() / 2,
                        event->scenePos().y() - refViewRectangle.height() / 2);

        m_model->insertConnectableItem(itemType.toStdString(), dropPos.x(), dropPos.y());
    }
}

//! Propagates elastic connection request between two views to the model.

void GraphicsScene::onConnectionRequest(ConnectableView* childView, ConnectableView* parentView)
{
    // Our current design implies that port type coincides with tag to use.
    auto tag = childView->outputPort()->portType().toStdString();

    // On model level connection of views means simply changing the parent of underlying items.
    m_model->moveItem(childView->connectableItem(), parentView->connectableItem(), {tag, -1});
}

//! Processes change in scene selection. Finds ConnectableItem corresponding to a selected view
//! and emit the signal.

void GraphicsScene::onSelectionChanged()
{
    auto selected = selectedViewItems<ConnectableView>();
    emit connectableItemSelectionChanged(selected.empty() ? nullptr
                                                          : selected.front()->connectableItem());
}

//! Disconnect views connected by the given connection.

void GraphicsScene::disconnectConnectedViews(NodeConnection* connection)
{
    // No actual view disconnection is going on here. We act on underlying ConnectableItem's.
    // All children items connected to the parents via this connection will be moved to the top of
    // the model (i.e. will become children of the model's root item). This in turn will trigger
    // corresponding ConnectableView recreation.

    auto childView = connection->childView();
    m_model->moveItem(childView->connectableItem(), m_model->rootItem(), {"", -1});
    // No need to delete the connection explicitly. It will be done by ConnectableView via its
    // ports.
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
    // Break explicitely selected connections.
    for (auto connection : selectedViewItems<NodeConnection>())
        disconnectConnectedViews(connection);

    // Remove selected views.
    for (auto view : selectedViewItems<ConnectableView>()) {

        // If the parent is intended to the deletion and has input connections, they have to be
        // disconnected first. This will prevent child item to be deleted when the parent is gone.
        for (auto connection : view->inputConnections())
            disconnectConnectedViews(connection);

        // deleting item
        ModelView::Utils::DeleteItemFromModel(view->connectableItem());
    }
}

//! Constructs a view for a given item and adds it to a scene, if necessary.
//! Connects new view with parent view.

void GraphicsScene::processItem(ConnectableItem* item)
{
    auto itemView = findView(item);
    if (!itemView) {
        itemView = new ConnectableView(item);
        m_itemToView[item] = itemView;
        addItem(itemView);
    }

    // If item has parent, look for parent's corresponding view. Connect it with itemView.
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
    auto it = m_itemToView.find(item);
    if (it != m_itemToView.end()) {
        delete it->second;
        m_itemToView.erase(it);
    }
}

} // namespace NodeEditor
