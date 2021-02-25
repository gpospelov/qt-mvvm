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

#include "mvvm/model/sessionitem.h"
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
    template <typename T> void addToGroup(const std::string& text = {}, bool make_selected = false);
    void updateCombo();

    int m_index_to_select;
    std::vector<std::string> m_item_text;
};

//! Adds an item of a given type to the group.
//! @param 'text' defines a text to be shown in ComboEditor when selecting an item in a group.
//! @param make_selected defines whether the item should be selected by default.
template <typename T> void GroupItem::addToGroup(const std::string& text, bool make_selected)
{
    m_item_text.push_back(text.empty() ? T().modelType() : text);
    insertItem<T>(TagRow::append(T_GROUP_ITEMS));
    if (make_selected)
        m_index_to_select = m_item_text.size() - 1;
    updateCombo();
}

} // namespace ModelView

#endif // MVVM_MODEL_GROUPITEM_H
