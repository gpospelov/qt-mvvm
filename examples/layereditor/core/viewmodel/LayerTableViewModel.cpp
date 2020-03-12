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
    : ViewModel(std::make_unique<LayerTableViewModelController>(model, this), parent)
{
}
