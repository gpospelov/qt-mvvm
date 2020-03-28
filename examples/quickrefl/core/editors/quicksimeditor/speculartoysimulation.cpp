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
const int sld_points_count = 400;
const int simulation_steps_count = 100;
}

using namespace ModelView;

SpecularToySimulation::SpecularToySimulation(const multislice_t &input_data)
    : input_data(input_data)
{
}

void SpecularToySimulation::runSimulation()
{
    // TODO
}

void SpecularToySimulation::setProgressCallback(ModelView::ProgressHandler::callback_t callback)
{
    progress_handler.setMaxTicksCount(simulation_steps_count);
    progress_handler.subscribe(callback);
}

SpecularToySimulation::Result SpecularToySimulation::simulationResult() const
{
    return sld_profile;
}

//! Calculates

void SpecularToySimulation::calculate_sld_profile()
{

}
