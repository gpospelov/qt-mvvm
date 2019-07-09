// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerTableViewModel.h"
#include "LayerTableViewModelController.h"

using namespace ModelView;

LayerTableViewModel::LayerTableViewModel(SessionModel* model, QObject* parent)
    : AbstractViewModel(std::make_unique<LayerTableViewModelController>(this), parent)
{
    setSessionModel(model);
}
