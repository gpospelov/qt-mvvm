// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "itemfactory.h"
#include "sessionitem.h"
#include "propertyitem.h"
#include "compounditem.h"
#include "vectoritem.h"
#include "itemcatalogue.h"

using namespace ModelView;

ItemFactory::ItemFactory() = default;

ItemFactory::ItemFactory(std::unique_ptr<ItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{

}

ItemFactory::~ItemFactory() = default;

SessionItem* ItemFactory::createItem(const model_type& modelType)
{
    if (modelType == Constants::PropertyType)
        return new PropertyItem;
    else if (modelType == Constants::CompoundType)
        return new CompoundItem;
    else if (modelType == Constants::VectorType)
        return new VectorItem;
    else if (modelType == Constants::BaseType)
        return new SessionItem;
    else
        throw std::runtime_error("ItemFactory::createItem() -> Unknown type '"+modelType+"'");
}

SessionItem* ItemFactory::createEmptyItem()
{
    return new SessionItem;
}
