// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/propertyflatviewmodel.h>
#include <mvvm/viewmodel/propertytableviewmodel.h>
#include <mvvm/viewmodel/propertyviewmodel.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/topitemsviewmodel.h>

using namespace ModelView;

std::unique_ptr<ViewModel> Utils::CreateDefaultViewModel(ModelView::SessionModel* model)
{
    return std::make_unique<DefaultViewModel>(model);
}

std::unique_ptr<ViewModel> Utils::CreatePropertyViewModel(SessionModel* model)
{
    return std::make_unique<PropertyViewModel>(model);
}

std::unique_ptr<ViewModel> Utils::CreatePropertyTableViewModel(SessionModel* model)
{
    return std::make_unique<PropertyTableViewModel>(model);
}

std::unique_ptr<ViewModel> Utils::CreateTopItemsViewModel(SessionModel* model)
{
    return std::make_unique<TopItemsViewModel>(model);
}

std::unique_ptr<ViewModel> Utils::CreatePropertyFlatViewModel(SessionModel* model)
{
    return std::make_unique<PropertyFlatViewModel>(model);
}
