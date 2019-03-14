// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "toy_models.h"
#include "toy_factories.h"
#include "toy_items.h"
#include "itemmanager.h"
#include "itemfactory.h"

namespace
{
std::unique_ptr<ModelView::ItemFactory> ToyItemFactory()
{
    return std::make_unique<ModelView::ItemFactory>(ToyItems::CreateToyItemCatalogue());
}
}


ToyItems::SampleModel::SampleModel()
    : SessionModel("ToyModel")
{
    m_item_manager->setItemFactory(std::make_unique<ToyItems::ItemFactory>());
}
