// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/propertyviewmodel.h>
#include <mvvm/viewmodel/topitemsviewmodel.h>
#include <mvvm/viewmodel/viewmodelbuilder.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

std::unique_ptr<AbstractViewModel> Utils::CreateDefaultViewModel(ModelView::SessionModel* model)
{
    auto controller = std::make_unique<DefaultViewModelController>();
    return ViewModelBuilder().setSessionModel(model).setController(std::move(controller)).build();
//    return std::make_unique<DefaultViewModel>(model);
}

std::unique_ptr<AbstractViewModel> Utils::CreatePropertyViewModel(SessionModel* model)
{
    return std::make_unique<PropertyViewModel>(model);
}

std::unique_ptr<AbstractViewModel> Utils::CreateTopItemsViewModel(SessionModel* model)
{
    return std::make_unique<TopItemsViewModel>(model);
}
