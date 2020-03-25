// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SPECULARTOYSIMULATION_H
#define SPECULARTOYSIMULATION_H

#include <mvvm/utils/progresshandler.h>
#include <vector>
#include "materialprofile.h"

//! Toy simulation to calculate "specular reflectivity.
//! Used by JobManager to run simulation in mylti-threaded mode.

class SpecularToySimulation
{
public:
    //! Data structure representing multi layer.
    using multilayer_t = std::vector<MaterialProfile::Slice>;

    //! Represents results of the simulation.
    struct Result {
        double xmin{0.0};
        double xmax{5.0};
        std::vector<double> data;
    };

    SpecularToySimulation(const multilayer_t& input_data);

    void runSimulation();

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

    Result simulationResult() const;

private:
    void calculate_sld_profile();

    ModelView::ProgressHandler progress_handler;
    multilayer_t input_data;
    Result sld_profile;
};

#endif // SPECULARTOYSIMULATION_H
