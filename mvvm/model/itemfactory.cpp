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

using namespace ModelView;

ItemFactory::ItemFactory()
{

}

SessionItem* ItemFactory::createItem(const model_type& modelType)
{
    return new SessionItem(modelType);
}

SessionItem* ItemFactory::createEmptyItem()
{
    return new SessionItem;
}
