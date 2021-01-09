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
#include "regionofinterestitem.h"
#include "mvvm/plotting/sceneadapterinterface.h"

using namespace ModelView;

namespace GraphicsProxy {

struct RegionOfInterestController::RegionOfInterestControllerImpl {
    const SceneAdapterInterface* m_sceneAdapter{nullptr};
    RegionOfInterestItem* m_item{nullptr};
    RegionOfInterestView* m_view{nullptr};
    bool m_blockOnPropertyChanged{false};
    QRectF m_roiRectangle;

    RegionOfInterestControllerImpl(const ModelView::SceneAdapterInterface* scene_adapter,
                                   RegionOfInterestItem* item, RegionOfInterestView* view)
        : m_sceneAdapter(scene_adapter), m_item(item), m_view(view)
    {
    }

    //! Updates item properties from the current view position.

    void updateItemFromView()
    {
        m_blockOnPropertyChanged = true;

        m_item->setProperty(RegionOfInterestItem::P_XLOW, m_sceneAdapter->fromSceneX(m_view->x()));
        m_item->setProperty(RegionOfInterestItem::P_XUP,
                            m_sceneAdapter->fromSceneX(m_view->x() + m_roiRectangle.width()));

        m_item->setProperty(RegionOfInterestItem::P_YLOW,
                            m_sceneAdapter->fromSceneY(m_view->y() + m_roiRectangle.height()));
        m_item->setProperty(RegionOfInterestItem::P_YUP, m_sceneAdapter->fromSceneY(m_view->y()));

        m_blockOnPropertyChanged = false;
    }

    //! Calculates view rectangle in scene coordinates from item properties.

    void setViewRectangleFromItem() { m_roiRectangle = QRectF(0.0, 0.0, width(), height()); }

    //! Sets view position in scene from item properties.

    void setViewPositionFromItem()
    {
        m_view->setX(m_sceneAdapter->toSceneX(par(RegionOfInterestItem::P_XLOW)));
        m_view->setY(m_sceneAdapter->toSceneY(par(RegionOfInterestItem::P_YUP)));
    }

    //! Updates view appearance using current values of item properties and state of scene adapter.

    void updateViewFromItem()
    {
        setViewRectangleFromItem();
        setViewPositionFromItem();
    }

    void updateItemFromCorner(double left, double right, double top, double bottom)
    {
        m_item->setProperty(RegionOfInterestItem::P_XLOW, m_sceneAdapter->fromSceneX(left));
        m_item->setProperty(RegionOfInterestItem::P_YLOW, m_sceneAdapter->fromSceneY(top));
        m_item->setProperty(RegionOfInterestItem::P_XUP, m_sceneAdapter->fromSceneX(right));
        m_item->setProperty(RegionOfInterestItem::P_YUP, m_sceneAdapter->fromSceneY(bottom));
    }

    void updateItemFromVerticalHandle(double top, double bottom)
    {
        m_item->setProperty(RegionOfInterestItem::P_YLOW, m_sceneAdapter->fromSceneY(top));
        m_item->setProperty(RegionOfInterestItem::P_YUP, m_sceneAdapter->fromSceneY(bottom));
    }

    void updateItemFromHorizontalHandle(double left, double right)
    {
        m_item->setProperty(RegionOfInterestItem::P_XLOW, m_sceneAdapter->fromSceneX(left));
        m_item->setProperty(RegionOfInterestItem::P_XUP, m_sceneAdapter->fromSceneX(right));
    }

    double width() const { return right() - left(); }
    double height() const { return bottom() - top(); }

    //! Returns the x-coordinate of the rectangle's left edge.
    double left() const { return m_sceneAdapter->toSceneX(par(RegionOfInterestItem::P_XLOW)); }

    //! Returns the x-coordinate of the rectangle's right edge.
    double right() const { return m_sceneAdapter->toSceneX(par(RegionOfInterestItem::P_XUP)); }

    //! Returns the y-coordinate of the rectangle's top edge.
    double top() const { return m_sceneAdapter->toSceneY(par(RegionOfInterestItem::P_YUP)); }

    //! Returns the y-coordinate of the rectangle's bottom edge.
    double bottom() const { return m_sceneAdapter->toSceneY(par(RegionOfInterestItem::P_YLOW)); }

    double par(const std::string& name) const { return m_item->property<double>(name); }
};

RegionOfInterestController::RegionOfInterestController(
    const ModelView::SceneAdapterInterface* scene_adapter, RegionOfInterestItem* item,
    RegionOfInterestView* view)
    : p_impl(std::make_unique<RegionOfInterestControllerImpl>(scene_adapter, item, view))
{
    setItem(item);
}

RegionOfInterestController::~RegionOfInterestController() = default;

QRectF RegionOfInterestController::roiRectangle() const
{
    return p_impl->m_roiRectangle;
}

//! Updates view appearance using current values of item properties and state of scene adapter.

void RegionOfInterestController::updateViewFromItem()
{
    p_impl->updateViewFromItem();
}

//! Updates item properties from current view position.

void RegionOfInterestController::updateItemFromView()
{
    p_impl->updateItemFromView();
}

//! Updates item properties using coordinates reported during corner resize.

void RegionOfInterestController::updateItemFromCorner(double left, double right, double top,
                                                      double bottom)
{
    p_impl->updateItemFromCorner(left, right, top, bottom);
}

//! Updates item properties using coordinates reported during vertical resize.

void RegionOfInterestController::updateItemFromVerticalHandle(double top, double bottom)
{
    p_impl->updateItemFromVerticalHandle(top, bottom);
}

//! Updates item properties using coordinates reported during horizontal resize.

void RegionOfInterestController::updateItemFromHorizontalHandle(double left, double right)
{
    p_impl->updateItemFromHorizontalHandle(left, right);
}

void RegionOfInterestController::subscribe()
{
    auto on_property_change = [this](auto, auto) {
        if (p_impl->m_blockOnPropertyChanged)
            return;

        p_impl->m_view->update_geometry();
        p_impl->m_view->update();
    };
    setOnPropertyChange(on_property_change);

    p_impl->updateViewFromItem();
}

} // namespace GraphicsProxy
