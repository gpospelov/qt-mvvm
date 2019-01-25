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
#include "itemmanager.h"

ToyItems::SampleModel::SampleModel()
    : SessionModel("ToyModel")
{
    m_item_manager->setItemFactory(std::make_unique<ToyItems::ItemFactory>());
}
