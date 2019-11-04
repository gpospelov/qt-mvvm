// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "compounditem.h"
#include "itemutils.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include <stdexcept>

using namespace ModelView;

namespace
{
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
