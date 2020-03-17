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

#include <QObject>
#include <atomic>
#include <mvvm/utils/threadsafestack.h>
#include <thread>
#include "toysimulation.h"

class GraphModel;

//! Handles all thread activity for running job simulation in the background.

class JobManager : public QObject
{
    Q_OBJECT
public:
    JobManager(GraphModel* model);
    ~JobManager();

    void requestSimulation(double value);

    void run_simulation();

    std::vector<double> getValues();

signals:
    void progressChanged(int value);
    void simulationCompleted();

public slots:
    void setDelay(int value);
    void onInterruptRequest();

private:
    std::thread sim_thread;
    GraphModel* model{nullptr};
    ModelView::threadsafe_stack<double> requested_values;
    ModelView::threadsafe_stack<ToySimulation::Result> simulation_results;
    std::atomic<bool> is_running;
    bool interrupt_request{false};
    int delay{0};
};

#endif // JOBMANAGER_H
