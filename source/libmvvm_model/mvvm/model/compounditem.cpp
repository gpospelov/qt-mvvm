// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/compounditem.h"
#include "mvvm/model/itemutils.h"

using namespace ModelView;

namespace {
bool has_custom_display_name(const SessionItem* item)
{
    return item->SessionItem::displayName() != item->modelType();
}
} // namespace

CompoundItem::CompoundItem(const std::string& modelType) : SessionItem(modelType) {}

std::string CompoundItem::displayName() const
{
    if (has_custom_display_name(this))
        return SessionItem::displayName();

    int copy_number = Utils::CopyNumber(this);
    return copy_number != -1 ? SessionItem::displayName() + std::to_string(copy_number)
                             : SessionItem::displayName();
}
