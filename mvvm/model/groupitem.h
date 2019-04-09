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

    const SessionItem* currentItem() const;

    std::string currentType() const;
    void setCurrentType(const std::string& model_type);

protected:
    void setCurrentIndex(int index);
    bool is_valid_index() const;
    template<typename T> void add(const std::string& text, bool make_selected=false);
    // FIXME how to make sure that init_group() was called in constructor?
    // Shell we delegate this call to CompoundItem::addProperty ?
    void init_group();
    std::unique_ptr<ItemCatalogue> m_catalogue;
    int m_default_selected_index;
};

template <typename T>
void GroupItem::add(const std::string& text, bool make_selected)
{
    m_catalogue->add<T>(text);
    if (make_selected)
        m_default_selected_index = m_catalogue->itemCount() - 1;
}

} // namespace ModelView

#endif // GROUPITEM_H
