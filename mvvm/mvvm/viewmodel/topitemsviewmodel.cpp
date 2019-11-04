// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "topitemsviewmodel.h"
#include "standardviewmodelcontrollers.h"

using namespace ModelView;

TopItemsViewModel::TopItemsViewModel(SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<TopItemsViewModelController>(this), parent)
{
    setSessionModel(model);
}
