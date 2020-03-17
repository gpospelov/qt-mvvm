// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "jobmanager.h"
#include "graphmodel.h"
#include "toysimulation.h"
#include <iostream>

JobManager::JobManager(GraphModel* model) : model(model), is_running(true)
{
    std::cout << "JobManager::JobManager() -> ctor" << std::endl;
    sim_thread = std::thread{&JobManager::run_simulation, this};
}

JobManager::~JobManager()
{
    std::cout << "JobManager::~JobManager() -> joining" << std::endl;
    requested_values.stop();
    is_running = false;
    sim_thread.join();
    std::cout << "JobManager::~JobManager() -> joined" << std::endl;
}

void JobManager::requestSimulation(double value)
{
    std::cout << "JobManager::requestSimulation() 1.1 -> saving value" << std::endl;
    requested_values.update_top(value);
    std::cout << "JobManager::requestSimulation() 1.2 -> value saved" << std::endl;
}

void JobManager::run_simulation()
{
    std::cout << "JobManager::run_simulation() 1.1" << std::endl;
    while (is_running) {
        std::cout << "JobManager::run_simulation() 1.2 -> in while" << std::endl;
        try {
            std::cout << "JobManager::run_simulation() 1.3 -> waiting for value " << std::endl;
            auto value = requested_values.wait_and_pop();
            std::cout << "JobManager::run_simulation() 1.4 -> obtained value " << value.get()
                      << std::endl;

            std::cout << "JobManager::run_simulation() 1.4.1 -> starting sim " << std::endl;
            double amplitude = *value.get() / 100.;
            ToySimulation simulation(amplitude, delay);

            auto on_progress = [this](int value) {
                progressChanged(value);
                return interrupt_request;
            };
            simulation.setProgressCallback(on_progress);

            simulation.runSimulation();
            auto result = simulation.simulationResult();
            model->set_data(result.data);
            std::cout << "JobManager::run_simulation() 1.4.2 -> sim done " << std::endl;

        } catch (std::exception ex) {
            std::cout << "JobManager::run_simulation() 1.5 -> terminated during waiting for value"
                      << std::endl;
        }
    }
}

void JobManager::setDelay(int value)
{
    delay = value;
}

