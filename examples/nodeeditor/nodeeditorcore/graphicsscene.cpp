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
#include "nodecontroller.h"
#include "sampleitems.h"
#include "samplemodel.h"
#include "mvvm/model/itemutils.h"
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
}

GraphicsScene::~GraphicsScene() = default;

//! Updates scene content from the model.

void GraphicsScene::updateScene()
{
    auto on_iterate = [this](auto item) {
        if (auto connectableItem = dynamic_cast<ConnectableItem*>(item); connectableItem)
            processItem(connectableItem);
    };
    ModelView::Utils::iterate(m_model->rootItem(), on_iterate);
}

//! Constructs a view for a given item and adds it to a scene, if necessary.
//! Connects new view with parent view.

void GraphicsScene::processItem(ConnectableItem* item)
{
    if (!findView(item)) {
        auto view = new ConnectableView(item);
        m_itemToView[item] = view;
        addItem(view);

        if (auto parentView = findView(dynamic_cast<ConnectableItem*>(item->parent())); parentView)
            parentView->makeChildConnected(view);
    }
}

//! Find view for given item.

ConnectableView* GraphicsScene::findView(ConnectableItem* item)
{
    auto it = m_itemToView.find(item);
    return it == m_itemToView.end() ? nullptr : it->second;
}

} // namespace NodeEditor
