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

using namespace ModelView;

ItemFactory::ItemFactory() = default;

// FIXME revise items which default factory should produce
SessionItem* ItemFactory::createItem(const model_type& modelType)
{
    if (modelType == Constants::PropertyType)
        return new PropertyItem;
    else if (modelType == Constants::CompoundType)
        return new CompoundItem;
    else
        return new SessionItem(modelType);
}

SessionItem* ItemFactory::createEmptyItem()
{
    return new SessionItem;
}
