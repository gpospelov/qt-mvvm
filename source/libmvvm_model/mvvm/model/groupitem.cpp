// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/groupitem.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/utils/containerutils.h"
#include <stdexcept>

using namespace ModelView;

namespace {

//! Returns vector of model types for given vector of items.
std::vector<std::string> modelTypes(const std::vector<SessionItem*>& items)
{
    std::vector<std::string> result;
    std::transform(items.begin(), items.end(), std::back_inserter(result),
                   [](auto item) { return item->modelType(); });
    return result;
}
} // namespace

GroupItem::~GroupItem() = default;

GroupItem::GroupItem(model_type modelType) : SessionItem(std::move(modelType)), m_index_to_select(0)
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
    return currentIndex() != -1 ? getItem("", currentIndex()) : nullptr;
}

SessionItem* GroupItem::currentItem()
{
    return const_cast<SessionItem*>(static_cast<const GroupItem*>(this)->currentItem());
}

std::string GroupItem::currentType() const
{
    return currentItem() ? currentItem()->modelType() : std::string();
}

//! Sets item corresponding to given model type.

void GroupItem::setCurrentType(const std::string& model_type)
{
    int index = Utils::IndexOfItem(modelTypes(children()), model_type);
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

//! Updates internal data representing selection of items, and current selection.
//! To be called during GroupItem's construction.

void GroupItem::updateCombo()
{
    ComboProperty combo;
    combo.setValues(m_item_text);
    combo.setCurrentIndex(m_index_to_select);
    setData(combo, ItemDataRole::DATA);
}
