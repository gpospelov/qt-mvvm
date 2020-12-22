// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/itemfactory.h"
#include "mvvm/model/itemcatalogue.h"
#include "mvvm/model/sessionitem.h"

using namespace ModelView;

ItemFactory::ItemFactory(std::unique_ptr<ItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{
}

void ItemFactory::registerItem(const std::string& modelType, item_factory_func_t func,
                               const std::string& label)
{
    m_catalogue->registerItem(modelType, func, label);
}

ItemFactory::~ItemFactory() = default;

std::unique_ptr<SessionItem> ItemFactory::createItem(const model_type& modelType) const
{
    return m_catalogue->create(modelType);
}
