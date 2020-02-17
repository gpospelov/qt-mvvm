// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ViewObject.h"
#include "GraphicsScene.h"
#include "mvvm/plotting/sceneadapterinterface.h"

#include <QPainter>

//! The constructor
ViewObject::ViewObject() : QGraphicsObject() {}

//! Get the conversion axes
ModelView::SceneAdapterInterface* ViewObject::getSceneAdapter() const
{
    GraphicsScene* scene_item = static_cast<GraphicsScene*>(scene());
    if (!scene_item)
        return nullptr;

    return scene_item->getSceneAdapter();
}

void ViewObject::advance(int phase)
{
    if (!phase)
        return;
    prepareGeometryChange();
    update();
}

void ViewObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setClipRect(getSceneAdapter()->viewportRectangle());
}
