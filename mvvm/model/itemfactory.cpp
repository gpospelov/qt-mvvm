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

ItemFactory::ItemFactory(std::unique_ptr<ItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{

}

ItemFactory::~ItemFactory() = default;

std::unique_ptr<SessionItem> ItemFactory::createItem(const model_type& modelType)
{
    auto result = create_intern(modelType);
//    result->setDisplayName(modelType); FIXME
    return result;
}

std::unique_ptr<SessionItem> ItemFactory::createEmptyItem()
{
    return std::make_unique<SessionItem>();
}

std::unique_ptr<SessionItem> ItemFactory::create_intern(const model_type& modelType) const
{
    return m_catalogue->create(modelType);
}
