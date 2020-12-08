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

#include <memory>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/sessionitem.h>

namespace ModelView
{

//! Group item holds collection of predefined items.

class MVVM_MODEL_EXPORT GroupItem : public SessionItem
{
public:
    static inline const std::string T_GROUP_ITEMS = "T_GROUP_ITEMS";

    GroupItem(model_type modelType = Constants::GroupItemType);
    ~GroupItem() override;

    int currentIndex() const;

    const SessionItem* currentItem() const;
    SessionItem* currentItem();

    std::string currentType() const;
    void setCurrentType(const std::string& model_type);

protected:
    void setCurrentIndex(int index);
    bool is_valid_index() const;
    template <typename T> void registerItem(const std::string& text, bool make_selected = false);
    // FIXME how to make sure that init_group() was called in constructor?
    // Shell we delegate this call to CompoundItem::addProperty ?
    void init_group();
    std::unique_ptr<ItemCatalogue> m_catalogue;
    int m_default_selected_index;
};

template <typename T> void GroupItem::registerItem(const std::string& text, bool make_selected)
{
    m_catalogue->registerItem<T>(text);
    if (make_selected)
        m_default_selected_index = m_catalogue->itemCount() - 1;
}

} // namespace ModelView

#endif // MVVM_MODEL_GROUPITEM_H
