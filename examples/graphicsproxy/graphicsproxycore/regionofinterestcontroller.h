// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXYCORE_REGIONOFINTERESTCONTROLLER_H
#define GRAPHICSPROXYCORE_REGIONOFINTERESTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include <memory>

class QRectF;

namespace ModelView {
class SceneAdapterInterface;
}

namespace GraphicsProxy {

class RegionOfInterestItem;
class RegionOfInterestView;

//! Establishes communications between RegionOfInterestItem and RegionOfInterestView.
//! Provides updates of view position/appearance on graphics scene, when underlying item changes.
//! Similarly, provides update of item's properties when view is moved/resized by the user.

class RegionOfInterestController : public ModelView::ItemListener<RegionOfInterestItem> {
public:
    RegionOfInterestController(const ModelView::SceneAdapterInterface* scene_adapter,
                               RegionOfInterestItem* item, RegionOfInterestView* view);
    ~RegionOfInterestController() override;

    QRectF roiRectangle() const;

    void updateViewFromItem();

    void updateItemFromView();

    void updateItemFromCorner(double left, double right, double top, double bottom);

    void updateItemFromVerticalHandle(double top, double bottom);

    void updateItemFromHorizontalHandle(double left, double right);

protected:
    void subscribe() override;

private:
    struct RegionOfInterestControllerImpl;
    std::unique_ptr<RegionOfInterestControllerImpl> p_impl;
};

} // namespace GraphicsProxy

#endif // GRAPHICSPROXYCORE_REGIONOFINTERESTCONTROLLER_H
