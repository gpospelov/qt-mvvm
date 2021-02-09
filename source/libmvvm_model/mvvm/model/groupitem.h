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
    bool isValidIndex() const;
    template <typename T> void addItem(const std::string& text, bool make_selected = false);
    void updateCombo();

    int m_default_selected_index;
    std::vector<std::string> m_item_labels;
};

//! Adds item of given type to the group. Make it selected if necessary.

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
