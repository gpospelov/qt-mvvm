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

JobManager::JobManager(GraphModel* model) : model(model) {}

void JobManager::requestSimulation(double value)
{
    ToySimulation simulation(value / 100., 1);
    simulation.runSimulation();
    auto result = simulation.simulationResult();
    model->set_data(result.data);
}
