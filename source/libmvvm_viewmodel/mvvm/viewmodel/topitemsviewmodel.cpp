// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/topitemsviewmodel.h"
#include "mvvm/viewmodel/standardviewmodelcontrollers.h"

using namespace ModelView;

TopItemsViewModel::TopItemsViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<TopItemsViewModelController>(model, this), parent)
{
}
