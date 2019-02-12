// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "compounditem.h"
#include "taginfo.h"
#include "sessionmodel.h"
#include "itemmanager.h"
#include "itemutils.h"
#include <stdexcept>

using namespace ModelView;

CompoundItem::CompoundItem(const std::string& modelType)
    : SessionItem(modelType)
{

}

std::string CompoundItem::displayName() const
{
    int copy_number = Utils::CopyNumber(this);
    return copy_number!=-1 ? SessionItem::displayName()+std::to_string(copy_number) : SessionItem::displayName();
}

QVariant CompoundItem::getItemValue(const std::string& tag) const
{
    return getItem(tag)->data(ItemDataRole::DATA);
}

void CompoundItem::setItemValue(const std::string& tag, const QVariant& variant)
{
    getItem(tag)->setData(variant, ItemDataRole::DATA);
}

