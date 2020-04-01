// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef QUICKSIMCONTROLLER_H
#define QUICKSIMCONTROLLER_H

#include "slice.h"
#include <QObject>
#include <memory>

class ApplicationModels;
class MaterialModel;
class SampleModel;
class JobModel;
class JobManager;

//! Provides quick reflectometry simulations on any change of SampleModel and MaterialModel.
//! Listens for any change in SampleModel and MaterialModel, extracts the data needed for
//! the simulation, and then submit simulation request to JobManager. As soon as JobManager reports
//! about completed simulations, extract results from there and put them into JobModel.

class QuickSimController : public QObject
{
    Q_OBJECT
public:
    // TODO Move JobModel into ApplicationModels
    QuickSimController(ApplicationModels* app_models, JobModel* job_model,
                       QObject* parent = nullptr);
    ~QuickSimController();

signals:
    void progressChanged(int value);

public slots:
    void onInterruptRequest();

private slots:
    void onMultiLayerChange();
    void onSimulationCompleted();

private:
    void setup_multilayer_tracking();
    void update_sld_profile(const multislice_t& multilayer);
    void submit_specular_simulation(const multislice_t& multislice);
    void setup_jobmanager_connections();

    SampleModel* sample_model{nullptr};
    MaterialModel* material_model{nullptr};
    JobModel* job_model{nullptr};
    JobManager* job_manager{nullptr};
};

#endif // QUICKSIMCONTROLLER_H
