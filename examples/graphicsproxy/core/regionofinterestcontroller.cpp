// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "regionofinterestcontroller.h"
#include "regionofinterestview.h"
#include "sceneitems.h"
#include <mvvm/plotting/sceneadapterinterface.h>

using namespace ModelView;

struct RegionOfInterestController::RegionOfInterestControllerImpl {
    RegionOfInterestItem* roi_item{nullptr};
    const SceneAdapterInterface* scene_adapter{nullptr};
    RegionOfInterestView* roi_view{nullptr};
    bool block_on_property_changed{false};
    QRectF roi_rectangle;

    RegionOfInterestControllerImpl(RegionOfInterestItem* item,
                                   const ModelView::SceneAdapterInterface* scene_adapter,
                                   RegionOfInterestView* view)
        : roi_item(item), scene_adapter(scene_adapter), roi_view(view)
    {
    }

    //! Updates properties of RegionOfInterestItem on any move performed by the user on scene.

    void update_item_from_view()
    {
        block_on_property_changed = true;

        roi_item->setProperty(RegionOfInterestItem::P_XLOW,
                              scene_adapter->fromSceneX(roi_view->x()));
        roi_item->setProperty(RegionOfInterestItem::P_XUP,
                              scene_adapter->fromSceneX(roi_view->x() + roi_rectangle.width()));

        roi_item->setProperty(RegionOfInterestItem::P_YLOW,
                              scene_adapter->fromSceneY(roi_view->y() + roi_rectangle.height()));
        roi_item->setProperty(RegionOfInterestItem::P_YUP,
                              scene_adapter->fromSceneY(roi_view->y()));

        block_on_property_changed = false;
    }

    //! Calculates view rectangle in scene coordinates from item properties.

    void set_view_rectangle_from_item() { roi_rectangle = QRectF(0.0, 0.0, width(), height()); }

    //! Sets view position in scene from item properties.

    void set_view_position_from_item()
    {
        roi_view->setX(scene_adapter->toSceneX(par(RegionOfInterestItem::P_XLOW)));
        roi_view->setY(scene_adapter->toSceneY(par(RegionOfInterestItem::P_YUP)));
    }

    //! Sets view appearance from item properties and current state of scene adapter.

    void update_geometry()
    {
        set_view_rectangle_from_item();
        set_view_position_from_item();
    }

    double width() const { return right() - left(); }
    double height() const { return bottom() - top(); }
    double left() const { return scene_adapter->toSceneX(par(RegionOfInterestItem::P_XLOW)); }
    double right() const { return scene_adapter->toSceneX(par(RegionOfInterestItem::P_XUP)); }
    double top() const { return scene_adapter->toSceneY(par(RegionOfInterestItem::P_YUP)); }
    double bottom() const { return scene_adapter->toSceneY(par(RegionOfInterestItem::P_YLOW)); }
    double par(const std::string& name) const { return roi_item->property(name).value<double>(); }
};

RegionOfInterestController::RegionOfInterestController(
    RegionOfInterestItem* item, const ModelView::SceneAdapterInterface* scene_adapter,
    RegionOfInterestView* view)
    : p_impl(std::make_unique<RegionOfInterestControllerImpl>(item, scene_adapter, view))
{
    setItem(item);
}

RegionOfInterestController::~RegionOfInterestController() = default;

QRectF RegionOfInterestController::roi_rectangle() const
{
    return p_impl->roi_rectangle;
}

void RegionOfInterestController::update_view_from_item()
{
    p_impl->update_geometry();
}

void RegionOfInterestController::update_item_from_view()
{
    p_impl->update_item_from_view();
}

void RegionOfInterestController::subscribe()
{
    auto on_property_change = [this](SessionItem*, std::string) {
        if (p_impl->block_on_property_changed)
            return;

        p_impl->update_geometry();
    };
    currentItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->update_geometry();
}
