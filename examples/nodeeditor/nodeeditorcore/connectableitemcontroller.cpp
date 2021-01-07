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
        m_item->setX(m_view->x());
        m_item->setY(m_view->y());
        m_blockOnPropertyChanged = false;
    }
};

ConnectableItemController::ConnectableItemController(ConnectableItem* item, ConnectableView* view)
    : p_impl(std::make_unique<ConnectableItemControllerImpl>(item, view))
{
}

//! Updates item properties from the current view position.

void ConnectableItemController::updateItemFromView()
{
    p_impl->updateItemFromView();
}

ConnectableItemController::~ConnectableItemController() = default;

void ConnectableItemController::subscribe() {}

} // namespace NodeEditor
