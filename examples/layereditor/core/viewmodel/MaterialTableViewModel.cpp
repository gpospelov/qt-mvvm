// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MaterialTableViewModel.h"
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

MaterialTableViewModel::MaterialTableViewModel(ModelView::SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<PropertyTableViewModelController>(this), parent)
{
    setSessionModel(model);
}
