// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TOYFACTORIES_H
#define TOYFACTORIES_H

#include "itemfactoryinterface.h"

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

class ItemFactory : public ModelView::ItemFactoryInterface
{
public:
    ModelView::SessionItem* createItem(const ModelView::model_type& modelType = {}) override;

    ModelView::SessionItem* createEmptyItem() override;
};

} // ToyItems

#endif // TOYFACTORIES_H

