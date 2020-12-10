// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "jobmanager.h"
#include "toysimulation.h"

JobManager::JobManager(QObject* parent) : QObject(parent), is_running(true)
{
    // starting thread to run consequent simulations
    sim_thread = std::thread{&JobManager::wait_and_run, this};
}

JobManager::~JobManager()
{
    is_running = false;
    requested_values.stop(); // stops waiting in JobManager::wait_and_run
    sim_thread.join();
}

//! Returns vector representing results of simulation.

std::vector<double> JobManager::simulationResult()
{
    auto value = simulation_results.try_pop();
    return value ? value->data : std::vector<double>{};
}

//! Performs simulation request. Given value will be stored in a stack of values to trigger
//! corresponding waiting thread.

void JobManager::requestSimulation(double value)
{
    // We replace top value in a stack (non-empty stack means that simulation is still running
    // for previous value).
    requested_values.update_top(value);
}

//! Saves simulation delay parameter for later use.

void JobManager::setDelay(int value)
{
    delay = value;
}

//! Processes interrupt request by setting corresponding flag.

void JobManager::onInterruptRequest()
{
    interrupt_request = true;
}

//! Performs concequent simulations for given simulation parameter. Waits for simulation input
//! parameter to appear in a stack, starts new simulation as soon as input data is ready.
//! Method is intended for execution in a thread.

void JobManager::wait_and_run()
{
    while (is_running) {
        try {
            // Waiting here for the value which we will use as simulation input parameter.
            auto value = requested_values.wait_and_pop();

            double amplitude = *value.get() / 100.;
            ToySimulation simulation(amplitude, delay);

            auto on_progress = [this](int value) {
                progressChanged(value);
                return interrupt_request;
            };
            simulation.setProgressCallback(on_progress);

            simulation.runSimulation();

            // Saving simulation result, overwrite previous if exists. If at this point stack
            // with results is not empty it means that plotting is disabled or running too slow.
            simulation_results.update_top(simulation.simulationResult());
            simulationCompleted();

        } catch (std::exception ex) {
            // Exception is thrown
            // a) If waiting on stack was stopped my calling threadsafe_stack::stop.
            // b) If simulation was interrupted via interrupt_request
            interrupt_request = false;
        }
    }
}
