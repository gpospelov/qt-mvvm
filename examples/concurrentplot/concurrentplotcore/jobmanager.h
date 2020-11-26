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

#include "toysimulation.h"
#include <QObject>
#include <mvvm/utils/threadsafestack.h>

//! Handles all thread activity for running job simulation in the background.

class JobManager : public QObject
{
    Q_OBJECT

public:
    JobManager(QObject* parent = nullptr);
    ~JobManager() override;

    std::vector<double> simulationResult();

signals:
    void progressChanged(int value);
    void simulationCompleted();

public slots:
    void requestSimulation(double value);
    void setDelay(int value);
    void onInterruptRequest();

private:
    void wait_and_run();

    std::thread sim_thread;
    ModelView::threadsafe_stack<double> requested_values;
    ModelView::threadsafe_stack<ToySimulation::Result> simulation_results;
    std::atomic<bool> is_running;
    bool interrupt_request{false};
    int delay{0};
};

#endif // JOBMANAGER_H
