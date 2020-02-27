// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/propertytableviewmodel.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

PropertyTableViewModel::PropertyTableViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<PropertyTableViewModelController>(model, this), parent)
{
}
