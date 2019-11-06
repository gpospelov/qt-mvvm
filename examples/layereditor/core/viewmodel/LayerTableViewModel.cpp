// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
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
