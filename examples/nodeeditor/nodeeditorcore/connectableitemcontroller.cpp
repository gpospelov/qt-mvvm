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
};

ConnectableItemController::ConnectableItemController(ConnectableItem* item, ConnectableView* view)
    : p_impl(std::make_unique<ConnectableItemControllerImpl>(item, view))
{
}

ConnectableItemController::~ConnectableItemController() = default;

void ConnectableItemController::subscribe()
{

}

} // namespace NodeEditor
