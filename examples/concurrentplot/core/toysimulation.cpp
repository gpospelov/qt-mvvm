// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "toysimulation.h"
#include <chrono>
#include <cmath>
#include <thread>

namespace
{
constexpr double pi = 3.14159265358979323846;
}

//! Run of heavy toy computational task.

ToySimulation::ToySimulation(double amplitude, int delay) : delay(delay)
{
    input_data.amplitude = amplitude;
}

void ToySimulation::runSimulation()
{
    result.data.clear();
    result.xmin = input_data.xmin;
    result.xmax = input_data.xmax;

    const double dx = (input_data.xmax - input_data.xmin) / input_data.npoints;
    for (int i = 0; i < input_data.npoints; ++i) {
        double x = input_data.xmin + i * dx;
        double value = input_data.amplitude * 10.0 * std::sin(2.0 * pi * 2 * x)
                       + input_data.amplitude * 5.0 * std::sin(2 * pi * 2.25 * x);
        result.data.push_back(value);

        if (delay > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

//! Returns result of toy simulation.

ToySimulation::Result ToySimulation::simulationResult() const
{
    return result;
}
