// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <mvvm/utils/threadsafestack.h>

class GraphModel;

//! Handles all thread activity for running job simulation in the background.

class JobManager
{
public:
    JobManager(GraphModel* model);

    void requestSimulation(double value);

private:
    GraphModel* model{nullptr};
};

#endif // JOBMANAGER_H
