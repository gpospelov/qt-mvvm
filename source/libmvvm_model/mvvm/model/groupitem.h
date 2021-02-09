// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_GROUPITEM_H
#define MVVM_MODEL_GROUPITEM_H

#include "mvvm/model/itemcatalogue.h"
#include "mvvm/model/sessionitem.h"
#include <memory>
#include <vector>

namespace ModelView {

//! Group item holds collection of predefined items.
//! Intended for the inheritance.

class MVVM_MODEL_EXPORT GroupItem : public SessionItem {
public:
    static inline const std::string T_GROUP_ITEMS = "T_GROUP_ITEMS";

    ~GroupItem() override;

    int currentIndex() const;

    const SessionItem* currentItem() const;
    SessionItem* currentItem();

    std::string currentType() const;
    void setCurrentType(const std::string& model_type);

protected:
    GroupItem(model_type modelType);

    void setCurrentIndex(int index);
    bool is_valid_index() const;
    template <typename T> void registerItem(const std::string& text, bool make_selected = false);
    // FIXME how to make sure that init_group() was called in constructor?
    // Shell we delegate this call to CompoundItem::addProperty ?
    void init_group();

    template <typename T> void addItem(const std::string& text, bool make_selected = false);
    void updateCombo();

    std::unique_ptr<ItemCatalogue> m_catalogue;
    int m_default_selected_index;
    std::vector<std::string> m_item_labels;
};

template <typename T> void GroupItem::registerItem(const std::string& text, bool make_selected)
{
    m_catalogue->registerItem<T>(text);
    if (make_selected)
        m_default_selected_index = m_catalogue->itemCount() - 1;
}

template <typename T> void GroupItem::addItem(const std::string& text, bool make_selected)
{
    m_item_labels.push_back(text);
    insertItem(new T, TagRow::append(T_GROUP_ITEMS));
    if (make_selected)
        m_default_selected_index = m_item_labels.size() - 1;
    updateCombo();
}

} // namespace ModelView

#endif // MVVM_MODEL_GROUPITEM_H
