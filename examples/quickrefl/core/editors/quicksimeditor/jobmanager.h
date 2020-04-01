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

#include "speculartoysimulation.h"
#include <QObject>
#include <mvvm/utils/threadsafestack.h>

//! Handles all thread activity for running job simulation in the background.

class JobManager : public QObject
{
    Q_OBJECT
public:
    JobManager(QObject* parent = nullptr);
    ~JobManager() override;

    SpecularToySimulation::Result simulationResult();

signals:
    void progressChanged(int value);
    void simulationCompleted();

public slots:
    void requestSimulation(const multislice_t& multislice);
    void onInterruptRequest();

private:
    void wait_and_run();

    std::thread sim_thread;
    ModelView::threadsafe_stack<multislice_t> requested_values;
    ModelView::threadsafe_stack<SpecularToySimulation::Result> simulation_results;
    std::atomic<bool> is_running;
    bool interrupt_request{false};
};

#endif // JOBMANAGER_H
