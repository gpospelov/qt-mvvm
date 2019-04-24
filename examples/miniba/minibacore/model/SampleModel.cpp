// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SampleModel.h"
#include "ItemCatalogue.h"
#include "itemmanager.h"
#include "itemfactory.h"

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    m_item_manager->setItemFactory(
        std::make_unique<ModelView::ItemFactory>(CreateItemCatalogue()));
}
