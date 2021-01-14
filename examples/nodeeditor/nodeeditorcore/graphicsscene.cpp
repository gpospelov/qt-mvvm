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
#include "nodecontroller.h"
#include "sampleitems.h"
#include "samplemodel.h"
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

//! Updates scene content from the model.

void GraphicsScene::updateScene()
{
    auto on_iterate = [this](auto item) {
        if (auto connectableItem = dynamic_cast<ConnectableItem*>(item); connectableItem)
            processItem(connectableItem);
    };
    ModelView::Utils::iterate(m_model->rootItem(), on_iterate);
}

//! Deletes item of selected type.

void GraphicsScene::onDeleteSelectedRequest()
{
    qDebug() << "GraphicsScene::onDeleteSelectedRequest()";
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

    if (auto parentView = findView(dynamic_cast<ConnectableItem*>(item->parent())); parentView)
        parentView->makeChildConnected(itemView);
}

//! Find view for given item.

ConnectableView* GraphicsScene::findView(ConnectableItem* item)
{
    auto it = m_itemToView.find(item);
    return it == m_itemToView.end() ? nullptr : it->second;
}

} // namespace NodeEditor
