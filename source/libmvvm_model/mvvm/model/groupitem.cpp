// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/comboproperty.h>
#include <mvvm/model/groupitem.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/utils/containerutils.h>
#include <stdexcept>

using namespace ModelView;

GroupItem::~GroupItem() = default;

GroupItem::GroupItem(model_type modelType)
    : SessionItem(std::move(modelType))
    , m_catalogue(std::make_unique<ItemCatalogue>())
    , m_default_selected_index(0)
{
    registerTag(TagInfo::universalTag(T_GROUP_ITEMS), /*set_as_default*/ true);
    setData(ComboProperty());
}

int GroupItem::currentIndex() const
{
    return data<ComboProperty>().currentIndex();
}

//! Returns currently selected item.

const SessionItem* GroupItem::currentItem() const
{
    return is_valid_index() ? getItem("", currentIndex()) : nullptr;
}

SessionItem* GroupItem::currentItem()
{
    return const_cast<SessionItem*>(static_cast<const GroupItem*>(this)->currentItem());
}

std::string GroupItem::currentType() const
{
    return is_valid_index() ? m_catalogue->modelTypes()[static_cast<size_t>(currentIndex())] : "";
}

//! Sets item corresponding to given model type.

void GroupItem::setCurrentType(const std::string& model_type)
{
    auto model_types = m_catalogue->modelTypes();
    int index = Utils::IndexOfItem(model_types, model_type);
    if (index == -1)
        throw std::runtime_error("GroupItem::setCurrentType() -> Model type '" + model_type
                                 + "' doesn't belong to the group");

    setCurrentIndex(index);
}

void GroupItem::setCurrentIndex(int index)
{
    auto combo = data<ComboProperty>();
    combo.setCurrentIndex(index);
    setData(combo, ItemDataRole::DATA);
}

bool GroupItem::is_valid_index() const
{
    return currentIndex() != -1;
}

//! Inits group item by creating all registered items and constructing combo property
//! for switching between items.

void GroupItem::init_group()
{
    ComboProperty combo;
    combo.setValues(m_catalogue->labels());
    combo.setCurrentIndex(m_default_selected_index);
    setData(combo, ItemDataRole::DATA);
    for (const auto& x : m_catalogue->modelTypes())
        insertItem(m_catalogue->create(x).release(), TagRow::append(T_GROUP_ITEMS));
}
