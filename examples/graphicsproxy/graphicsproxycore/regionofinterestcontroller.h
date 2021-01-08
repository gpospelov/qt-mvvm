// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_REGIONOFINTERESTCONTROLLER_H
#define GRAPHICSPROXY_REGIONOFINTERESTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include <memory>

namespace ModelView {
class SceneAdapterInterface;
}

class RegionOfInterestItem;
class RegionOfInterestView;
class QRectF;

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

#endif // GRAPHICSPROXY_REGIONOFINTERESTCONTROLLER_H
