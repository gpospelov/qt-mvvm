// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_GROUPITEM_H
#define MVVM_GROUPITEM_H

#include <mvvm/model/sessionitem.h>
#include <mvvm/model/itemcatalogue.h>
#include <memory>

namespace ModelView {

//! Group item holds collection of predefined items.

class CORE_EXPORT GroupItem : public SessionItem
{
public:
    GroupItem(model_type modelType = Constants::GroupItemType);
    ~GroupItem() override;

    int currentIndex() const;

    const SessionItem* currentItem() const;

    std::string currentType() const;
    void setCurrentType(const std::string& model_type);

protected:
    void setCurrentIndex(int index);
    bool is_valid_index() const;
    template<typename T> void registerItem(const std::string& text, bool make_selected=false);
    // FIXME how to make sure that init_group() was called in constructor?
    // Shell we delegate this call to CompoundItem::addProperty ?
    void init_group();
    std::unique_ptr<ItemCatalogue> m_catalogue;
    int m_default_selected_index;
};

template <typename T>
void GroupItem::registerItem(const std::string& text, bool make_selected)
{
    m_catalogue->registerItem<T>(text);
    if (make_selected)
        m_default_selected_index = m_catalogue->itemCount() - 1;
}

} // namespace ModelView

#endif // MVVM_GROUPITEM_H
