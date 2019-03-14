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

#include "global.h"
#include "itemfactoryinterface.h"
#include <memory>

namespace ModelView
{

class ItemCatalogue;

//! Default SessionItem factory.

class CORE_EXPORT ItemFactory : public ItemFactoryInterface
{
public:
    ItemFactory(std::unique_ptr<ItemCatalogue> catalogue);
    ~ItemFactory() override;

    std::unique_ptr<SessionItem> createItem(const model_type& modelType = {}) const override;

    std::unique_ptr<SessionItem> createEmptyItem() const override;

protected:
    std::unique_ptr<SessionItem> create_intern(const model_type& modelType) const;
    std::unique_ptr<ItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif
