// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMCATALOGUE_H
#define MVVM_MODEL_ITEMCATALOGUE_H

#include "mvvm/model/function_types.h"
#include "mvvm/model_export.h"
#include <string>
#include <vector>

namespace ModelView {

class SessionItem;

//! Catalogue for item constructions. Contains collection of factory functions associated with
//! item's modelType and optional label.

class MVVM_MODEL_EXPORT ItemCatalogue {
public:
    ItemCatalogue();
    ~ItemCatalogue();

    ItemCatalogue(const ItemCatalogue& other);
    ItemCatalogue& operator=(const ItemCatalogue& other);

    template <typename T> void registerItem(const std::string& label = {});

    void registerItem(const std::string& modelType, item_factory_func_t func,
                      const std::string& label);

    bool contains(const std::string& modelType) const;

    std::unique_ptr<SessionItem> create(const std::string& modelType) const;

    std::vector<std::string> modelTypes() const;

    std::vector<std::string> labels() const;

    int itemCount() const;

    void merge(const ItemCatalogue& other);

private:
    struct ItemCatalogueImpl;
    std::unique_ptr<ItemCatalogueImpl> p_impl;
};

template <typename T> void ItemCatalogue::registerItem(const std::string& label)
{
    registerItem(T().modelType(), ItemFactoryFunction<T>(), label);
}

} // namespace ModelView

#endif // MVVM_MODEL_ITEMCATALOGUE_H
