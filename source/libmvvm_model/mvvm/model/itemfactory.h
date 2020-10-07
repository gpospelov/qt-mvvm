// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMFACTORY_H
#define MVVM_MODEL_ITEMFACTORY_H

#include <memory>
#include <mvvm/interfaces/itemfactoryinterface.h>
#include <mvvm/model_export.h>

namespace ModelView
{

class ItemCatalogue;

//! Default SessionItem factory.

class MVVM_MODEL_EXPORT ItemFactory : public ItemFactoryInterface
{
public:
    ItemFactory(std::unique_ptr<ItemCatalogue> catalogue);
    ~ItemFactory() override;

    std::unique_ptr<SessionItem> createItem(const model_type& modelType) const override;

    std::unique_ptr<SessionItem> createEmptyItem() const override;

protected:
    std::unique_ptr<ItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMFACTORY_H
