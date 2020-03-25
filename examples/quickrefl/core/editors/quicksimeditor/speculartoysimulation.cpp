// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "speculartoysimulation.h"

namespace
{
const int simulation_steps_count = 100;
}

using namespace ModelView;

SpecularToySimulation::SpecularToySimulation(const SpecularToySimulation::multilayer_t& input_data)
    : input_data(input_data)
{
}

void SpecularToySimulation::setProgressCallback(ModelView::ProgressHandler::callback_t callback)
{
    progress_handler.setMaxTicksCount(simulation_steps_count);
    progress_handler.subscribe(callback);
}
