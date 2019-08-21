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

CompoundItem::CompoundItem(const std::string& modelType) : SessionItem(modelType) {}

std::string CompoundItem::displayName() const
{
    int copy_number = Utils::CopyNumber(this);
    return copy_number != -1 ? SessionItem::displayName() + std::to_string(copy_number)
                             : SessionItem::displayName();
}
