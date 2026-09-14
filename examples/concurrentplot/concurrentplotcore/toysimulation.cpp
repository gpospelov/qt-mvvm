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
#include <stdexcept>
#include <thread>
#include <utility>

using namespace ModelView;

namespace {
constexpr double pi = 3.14159265358979323846;
}

//! Run of heavy toy computational task.

ToySimulation::ToySimulation(double amplitude, int delay) : m_delay(delay)
{
    m_progress_handler.setMaxTicksCount(m_input_data.npoints);
    m_input_data.amplitude = amplitude;
}

void ToySimulation::runSimulation()
{
    m_progress_handler.reset();
    m_result.data.clear();
    m_result.xmin = m_input_data.xmin;
    m_result.xmax = m_input_data.xmax;

    const double dx = (m_input_data.xmax - m_input_data.xmin) / m_input_data.npoints;
    for (int i = 0; i < m_input_data.npoints; ++i) {
        if (m_progress_handler.has_interrupt_request())
            throw std::runtime_error("Interrupt request");
        double x = m_input_data.xmin + i * dx;
        double value = m_input_data.amplitude * 10.0 * std::sin(2.0 * pi * 2 * x)
                       + m_input_data.amplitude * 5.0 * std::sin(2 * pi * 2.25 * x);
        m_result.data.push_back(value);

        m_progress_handler.setCompletedTicks(1);

        if (m_delay > 0)
            std::this_thread::sleep_for(std::chrono::microseconds(m_delay));
    }
}

//! Returns m_result of toy simulation.

ToySimulation::Result ToySimulation::simulationResult() const
{
    return m_result;
}

void ToySimulation::setProgressCallback(ProgressHandler::callback_t callback)
{
    m_progress_handler.subscribe(std::move(callback));
}
