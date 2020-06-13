// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "speculartoysimulation.h"
#include "fouriertransform.h"
#include "materialprofile.h"
#include <mvvm/utils/containerutils.h>
#include <thread>
#include <stdexcept>

namespace
{
const int delay_mksec = 5000;
const int simulation_steps_count = 500;
} // namespace

using namespace ModelView;

SpecularToySimulation::SpecularToySimulation(const multislice_t& multislice)
    : input_data(multislice)
{
}

void SpecularToySimulation::runSimulation()
{
    // actual simulation
    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(input_data);
    auto profile =
        MaterialProfile::CalculateProfile(input_data, simulation_steps_count, xmin, xmax);
    auto specular = fourier_transform(profile);
    specular_result.xmin = 0.0;
    specular_result.xmax = specular.size();
    specular_result.data = ModelView::Utils::Real(specular);

    // Mimicking long simulation time, reporting progress and canceling, if necessary.
    progress_handler.reset();
    for (int i = 0; i < simulation_steps_count; ++i) {
        if (progress_handler.has_interrupt_request())
            throw std::runtime_error("Interrupt request");

        progress_handler.setCompletedTicks(1);
        std::this_thread::sleep_for(std::chrono::microseconds(delay_mksec));
    }
}

void SpecularToySimulation::setProgressCallback(ModelView::ProgressHandler::callback_t callback)
{
    progress_handler.setMaxTicksCount(simulation_steps_count);
    progress_handler.subscribe(callback);
}

SpecularToySimulation::Result SpecularToySimulation::simulationResult() const
{
    return specular_result;
}

SpecularToySimulation::Result SpecularToySimulation::sld_profile(const multislice_t& multislice,
                                                                 int n_points)
{
    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(multislice);
    auto profile = MaterialProfile::CalculateProfile(multislice, n_points, xmin, xmax);
    return {xmin, xmax, ModelView::Utils::Real(profile)};
}
