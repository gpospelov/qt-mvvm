// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TOYSIMULATION_H
#define TOYSIMULATION_H

#include <mvvm/utils/progresshandler.h>
#include <vector>

//! Represents long running toy scientific simulation.

class ToySimulation
{
public:
    //! Represents input conditions for toy simulation.
    struct InputData {
        double xmin{0.0};
        double xmax{5.0};
        int npoints{400};
        double amplitude{1.0};
    };

    //! Represents results of the simulation.
    struct Result {
        double xmin{0.0};
        double xmax{5.0};
        std::vector<double> data;
    };

    ToySimulation(double amplitude = 1.0, int delay = 0.0);

    void runSimulation();

    Result simulationResult() const;

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

private:
    InputData input_data;
    Result result;
    int delay{0};
    ModelView::ProgressHandler progress_handler;
};

#endif //  TOYSIMULATION_H
