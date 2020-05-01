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

    //! Updates item properties from current view position.

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

    //! Updates view appearance using current values of item properties and state of scene adapter.

    void update_view_from_item()
    {
        set_view_rectangle_from_item();
        set_view_position_from_item();
    }

    void update_item_from_corner(double left, double right, double top, double bottom)
    {
        roi_item->setProperty(RegionOfInterestItem::P_XLOW, scene_adapter->fromSceneX(left));
        roi_item->setProperty(RegionOfInterestItem::P_YLOW, scene_adapter->fromSceneY(top));
        roi_item->setProperty(RegionOfInterestItem::P_XUP, scene_adapter->fromSceneX(right));
        roi_item->setProperty(RegionOfInterestItem::P_YUP, scene_adapter->fromSceneY(bottom));
    }

    void update_item_from_vertical_handle(double top, double bottom)
    {
        roi_item->setProperty(RegionOfInterestItem::P_YLOW, scene_adapter->fromSceneY(top));
        roi_item->setProperty(RegionOfInterestItem::P_YUP, scene_adapter->fromSceneY(bottom));
    }

    void update_item_from_horizontal_handle(double left, double right)
    {
        roi_item->setProperty(RegionOfInterestItem::P_XLOW, scene_adapter->fromSceneX(left));
        roi_item->setProperty(RegionOfInterestItem::P_XUP, scene_adapter->fromSceneX(right));
    }

    double width() const { return right() - left(); }
    double height() const { return bottom() - top(); }

    //! Returns the x-coordinate of the rectangle's left edge.
    double left() const { return scene_adapter->toSceneX(par(RegionOfInterestItem::P_XLOW)); }

    //! Returns the x-coordinate of the rectangle's right edge.
    double right() const { return scene_adapter->toSceneX(par(RegionOfInterestItem::P_XUP)); }

    //! Returns the y-coordinate of the rectangle's top edge.
    double top() const { return scene_adapter->toSceneY(par(RegionOfInterestItem::P_YUP)); }

    //! Returns the y-coordinate of the rectangle's bottom edge.
    double bottom() const { return scene_adapter->toSceneY(par(RegionOfInterestItem::P_YLOW)); }

    double par(const std::string& name) const { return roi_item->property<double>(name); }
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

//! Updates view appearance using current values of item properties and state of scene adapter.

void RegionOfInterestController::update_view_from_item()
{
    p_impl->update_view_from_item();
}

//! Updates item properties from current view position.

void RegionOfInterestController::update_item_from_view()
{
    p_impl->update_item_from_view();
}

//! Updates item properties using coordinates reported during corner resize.

void RegionOfInterestController::update_item_from_corner(double left, double right, double top,
                                                         double bottom)
{
    p_impl->update_item_from_corner(left, right, top, bottom);
}

//! Updates item properties using coordinates reported during vertical resize.

void RegionOfInterestController::update_item_from_vertical_handle(double top, double bottom)
{
    p_impl->update_item_from_vertical_handle(top, bottom);
}

//! Updates item properties using coordinates reported during horizontal resize.

void RegionOfInterestController::update_item_from_horizontal_handle(double left, double right)
{
    p_impl->update_item_from_horizontal_handle(left, right);
}

void RegionOfInterestController::subscribe()
{
    auto on_property_change = [this](SessionItem*, std::string) {
        if (p_impl->block_on_property_changed)
            return;

        p_impl->roi_view->update_geometry();
        p_impl->roi_view->update();
    };
    setOnPropertyChange(on_property_change);

    p_impl->update_view_from_item();
}
