// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/viewmodel/propertytableviewmodel.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

PropertyTableViewModel::PropertyTableViewModel(SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<PropertyTableViewModelController>(this), parent)
{
    setSessionModel(model);
}
