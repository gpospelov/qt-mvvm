// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMPOOL_H
#define MVVM_MODEL_ITEMPOOL_H

#include "mvvm/model_export.h"
#include <cstddef>
#include <map>
#include <string>

namespace ModelView {

class SessionItem;

//! Provides registration of SessionItem pointers and their unique identifiers
//! in global memory pool.

class MVVM_MODEL_EXPORT ItemPool {
public:
    ItemPool() = default;
    ItemPool(const ItemPool&) = delete;
    ItemPool(ItemPool&&) = delete;
    ItemPool& operator=(const ItemPool&) = delete;
    ItemPool& operator=(ItemPool&&) = delete;

    size_t size() const;

    std::string register_item(SessionItem* item, std::string key = {});
    void unregister_item(SessionItem* item);

    std::string key_for_item(const SessionItem* item) const;

    SessionItem* item_for_key(const std::string& key) const;

private:
    std::map<std::string, SessionItem*> m_key_to_item;
    std::map<const SessionItem*, std::string> m_item_to_key;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMPOOL_H
