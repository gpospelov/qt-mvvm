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

#include <memory>
#include <mvvm/signals/itemcontroller.h>

namespace ModelView
{
class SceneAdapterInterface;
}

class RegionOfInterestItem;
class RegionOfInterestView;
class QRectF;

//! Establishes communications between RegionOfInterestItem and RegionOfInterestView.
//! Provides updates of view position/appearance on graphics scene, when underlying item changes.
//! Similarly, provides update of item's properties when view is moved/resized by the user.

class RegionOfInterestController : public ModelView::ItemController<RegionOfInterestItem>
{
public:
    RegionOfInterestController(RegionOfInterestItem* item,
                               const ModelView::SceneAdapterInterface* scene_adapter,
                               RegionOfInterestView* view);
    ~RegionOfInterestController() override;

    QRectF roi_rectangle() const;

    void update_view_from_item();

    void update_item_from_view();

protected:
    void subscribe() override;

private:
    struct RegionOfInterestControllerImpl;
    std::unique_ptr<RegionOfInterestControllerImpl> p_impl;
};

#endif // GRAPHICSPROXY_REGIONOFINTERESTCONTROLLER_H
