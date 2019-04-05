// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef GROUPITEM_H
#define GROUPITEM_H

#include "sessionitem.h"
#include "itemcatalogue.h"
#include <memory>

namespace ModelView {

//! Group item holds collection of predefined items.

class CORE_EXPORT GroupItem : public SessionItem
{
public:
    GroupItem(model_type modelType = Constants::GroupType);
    ~GroupItem();

    int currentIndex() const;

    SessionItem* currentItem();

    std::string currentType() const;
    void setCurrentType(const std::string& model_type);

protected:
    bool is_valid_index() const;
    template<typename T> void add(const std::string& text, bool set_as_initial=false);
    void init_group();
    void update_combo();
    std::unique_ptr<ItemCatalogue> m_catalogue;
    int m_current_index;
};

template <typename T>
void GroupItem::add(const std::string& text, bool set_as_initial)
{
    m_catalogue->add<T>(text);
    m_current_index = set_as_initial ? m_catalogue->itemCount() - 1 : 0;
}

} // namespace ModelView

#endif // GROUPITEM_H
