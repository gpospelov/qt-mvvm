// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "axesrectangleview.h"
#include <mvvm/plotting/sceneadapterinterface.h>

AxesRectangleView::AxesRectangleView(const ModelView::SceneAdapterInterface* scene_adapter)
    : scene_adapter(scene_adapter)
{
    // the key flag to hide children going outside of *this* bounding rectangle
    setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
}

QRectF AxesRectangleView::boundingRect() const
{
    return rect;
}

//! Recalculates bounding rectangle using axes viewport as reported by the adapter.

void AxesRectangleView::advance(int phase)
{
    if (!phase)
        return;
    prepareGeometryChange();
    rect = scene_adapter->viewportRectangle();
}

void AxesRectangleView::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
    // nothing to paint
}
