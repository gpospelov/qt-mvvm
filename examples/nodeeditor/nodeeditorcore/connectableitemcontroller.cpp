// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "connectableitemcontroller.h"
#include "connectableview.h"
#include "sampleitems.h"

using namespace ModelView;

namespace NodeEditor {

struct ConnectableItemController::ConnectableItemControllerImpl {
    ConnectableItem* m_item{nullptr};
    ConnectableView* m_view{nullptr};
    bool m_blockOnPropertyChanged{false};

    ConnectableItemControllerImpl(ConnectableItem* item, ConnectableView* view)
        : m_item(item), m_view(view)
    {
    }

    //! Updates item properties from the current view position.

    void updateItemFromView()
    {
        m_blockOnPropertyChanged = true;
        m_item->setPos(m_view->x(), m_view->y());
        m_blockOnPropertyChanged = false;
    }

    //! Updates view position and appearance using current values of item properties.

    void updateViewFromItem()
    {
        m_view->setX(m_item->x());
        m_view->setY(m_item->y());
        m_view->update();
    }
};

ConnectableItemController::ConnectableItemController(ConnectableItem* item, ConnectableView* view)
    : p_impl(std::make_unique<ConnectableItemControllerImpl>(item, view))
{
    setItem(item);
}

//! Updates item properties from the current view position.

void ConnectableItemController::updateItemFromView()
{
    p_impl->updateItemFromView();
}

void ConnectableItemController::updateViewFromItem()
{
    p_impl->updateViewFromItem();
}

ConnectableItemController::~ConnectableItemController() = default;

void ConnectableItemController::subscribe()
{
    auto on_property_change = [this](auto, auto) {
        if (p_impl->m_blockOnPropertyChanged)
            return;
        p_impl->updateViewFromItem();
    };
    setOnPropertyChange(on_property_change);

    p_impl->updateViewFromItem();
}

} // namespace NodeEditor
