// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/viewmodel/propertyviewmodel.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

PropertyViewModel::PropertyViewModel(SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<PropertyViewModelController>(this), parent)
{
    setSessionModel(model);
}
