// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/materialtableviewmodel.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

MaterialTableViewModel::MaterialTableViewModel(ModelView::SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<PropertyTableViewModelController>(model, this), parent)
{
}
