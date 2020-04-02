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

#include "materialprofile.h"
#include <mvvm/utils/progresshandler.h>
#include <vector>

//! Toy simulation to calculate "specular reflectivity.
//! Used by JobManager to run simulation in mylti-threaded mode.

class SpecularToySimulation
{
public:
    //! Represents results of the simulation.
    struct Result {
        double xmin{0.0};
        double xmax{5.0};
        std::vector<double> data;
    };

    SpecularToySimulation(const multislice_t& multislice);

    void runSimulation();

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

    Result simulationResult() const;

    static Result sld_profile(const multislice_t& multislice, int n_points);

private:
    ModelView::ProgressHandler progress_handler;
    multislice_t input_data;
    Result specular_result;
};

#endif // SPECULARTOYSIMULATION_H
