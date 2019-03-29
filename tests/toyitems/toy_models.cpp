// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "toy_models.h"
#include "itemfactory.h"
#include "itemmanager.h"
#include "toy_items.h"

ToyItems::SampleModel::SampleModel() : SessionModel("ToyModel")
{
    m_item_manager->setItemFactory(
        std::make_unique<ModelView::ItemFactory>(ToyItems::CreateToyItemCatalogue()));
}
