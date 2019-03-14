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

#include "itemfactory.h"

namespace ModelView
{
class ItemCatalogue;
}

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

class ItemFactory : public ModelView::ItemFactory
{
public:
    ItemFactory(std::unique_ptr<ModelView::ItemCatalogue> catalogue);

    std::unique_ptr<ModelView::SessionItem> createItem(const ModelView::model_type& modelType = {}) override;

    std::unique_ptr<ModelView::SessionItem> createEmptyItem() override;
};

} // ToyItems

#endif // TOYFACTORIES_H

