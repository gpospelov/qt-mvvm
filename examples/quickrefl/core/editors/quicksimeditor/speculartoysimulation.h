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

//! Toy simulation to calculate "specular reflectivity.
//! Used by JobManager to run simulation in mylti-threaded mode.

class SpecularToySimulation
{
public:
    //! Layer parameters. Data structure to feed simulation with input parameters.
    struct Slice {
        double sld_real{0.0};
        double thickness{0.0};
    };

    using multilayer_t = std::vector<Slice>;

    SpecularToySimulation(const multilayer_t& input_data);

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

private:
    ModelView::ProgressHandler progress_handler;
    multilayer_t input_data;
};

#endif // SPECULARTOYSIMULATION_H
