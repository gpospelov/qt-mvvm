// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_CONNECTABLEITEMCONTROLLER_H
#define NODEEDITORCORE_CONNECTABLEITEMCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include <memory>

namespace NodeEditor {

class ConnectableItem;
class ConnectableView;

//! Establishes communications between ConnectableItem and ConnectableView.
//! Provides updates of view position/appearance on graphics scene, when underlying item changes.
//! Similarly, provides update of item's properties while view is moving on the scene.

class ConnectableItemController : public ModelView::ItemListener<ConnectableItem> {
public:
    ConnectableItemController(ConnectableItem* item, ConnectableView* view);
    ~ConnectableItemController() override;

    void updateItemFromView();
    void updateViewFromItem();

protected:
    void subscribe() override;

private:
    struct ConnectableItemControllerImpl;
    std::unique_ptr<ConnectableItemControllerImpl> p_impl;
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_CONNECTABLEITEMCONTROLLER_H
