// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "jobmanager.h"

JobManager::JobManager(QObject* parent) : QObject(parent), is_running(true)
{
    // starting thread to run consequent simulations
    sim_thread = std::thread{&JobManager::wait_and_run, this};
}

JobManager::~JobManager()
{
    is_running = false;
    requested_values.stop(); // making stack throw to stops waiting in JobManager::wait_and_run
    sim_thread.join();
}

//! Returns vector representing results of a simulation.

SpecularToySimulation::Result JobManager::simulationResult()
{
    auto result = simulation_results.try_pop();
    return result ? *result.get() : SpecularToySimulation::Result();
}

//! Performs simulation request. Given multislice will be stored in a stack of values to trigger
//! a waiting thread.

void JobManager::requestSimulation(const multislice_t& multislice)
{
    // At this point, non-empty stack means that currently simulation thread is busy.
    // Replacing top value in a stack, meaning that we are droping previous request.
    requested_values.update_top(multislice);
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

            // preparing simulation
            SpecularToySimulation simulation(*value.get());
            auto on_progress = [this](int value) {
                progressChanged(value);
                return interrupt_request;
            };
            simulation.setProgressCallback(on_progress);

            // running simulation
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
