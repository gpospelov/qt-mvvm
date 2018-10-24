// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "itemfactoryinterface.h"

namespace ModelView {

//! Default SessionItem factory.

class ItemFactory : public ItemFactoryInterface
{
public:
    ItemFactory();

    SessionItem* createItem(const model_type& modelType = {});

    SessionItem* createEmptyItem();

};

}  // namespace ModelView

#endif
