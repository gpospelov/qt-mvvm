// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "toy_factories.h"
#include "sessionitem.h"
#include "propertyitem.h"
#include "toy_constants.h"
#include "toy_items.h"
#include "vectoritem.h"
#include <stdexcept>

using namespace ToyItems;

ItemFactory::ItemFactory(std::unique_ptr<ModelView::ItemCatalogue> catalogue)
   : ModelView::ItemFactory(std::move(catalogue))
{

}

ModelView::SessionItem* ItemFactory::createItem(const ModelView::model_type& modelType)
{
    auto result = create_intern(modelType);

    result->setDisplayName(modelType);
    return result.release();
}

ModelView::SessionItem* ItemFactory::createEmptyItem()
{
    return new ModelView::SessionItem;
}
