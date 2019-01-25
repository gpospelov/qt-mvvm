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
#include <stdexcept>

using namespace ModelView;

CompoundItem::CompoundItem(const std::string& modelType)
    : SessionItem(modelType)
{

}

//! Registers single item tag and adds PropertyItem with given variant value.

SessionItem* CompoundItem::addProperty(const std::string& name, const QVariant& variant)
{
    if (!model())
        throw std::runtime_error("CompoundItem::addProperty() -> Can't create property, "
                                 "model is undefined");

    registerTag(TagInfo::propertyTag(name, Constants::PropertyType));

    // not inserting through SessionModel::insertNewItem to bypass unddo/redo
    auto propertyItem = model()->manager()->createItem(Constants::PropertyType);
    insertItem(0, propertyItem, name);

    propertyItem->setDisplayName(name);
    propertyItem->setData(variant, ItemDataRole::DATA);

    return propertyItem;
}
