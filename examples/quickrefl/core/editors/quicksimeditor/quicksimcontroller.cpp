// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "quicksimcontroller.h"
#include "applicationmodels.h"
#include "jobmanager.h"
#include "jobmodel.h"
#include "layeritems.h"
#include "materialmodel.h"
#include "materialprofile.h"
#include "quicksimutils.h"
#include "samplemodel.h"
#include "slice.h"
#include "speculartoysimulation.h"
#include <QDebug>
#include <mvvm/model/modelutils.h>
#include <mvvm/signals/modelmapper.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphviewportitem.h>

namespace
{
const int profile_points_count = 400;
}

QuickSimController::QuickSimController(ApplicationModels* app_models, JobModel* job_model,
                                       QObject* parent)
    : QObject(parent), sample_model(app_models->sampleModel()),
      material_model(app_models->materialModel()), job_model(job_model),
      job_manager(new JobManager(this))
{
    setup_multilayer_tracking();
    setup_jobmanager_connections();
}

QuickSimController::~QuickSimController()
{
    if (material_model)
        material_model->mapper()->unsubscribe(this);
    if (sample_model)
        sample_model->mapper()->unsubscribe(this);
}

//! Requests interruption of running simulaitons.

void QuickSimController::onInterruptRequest()
{
    job_manager->onInterruptRequest();
}

void QuickSimController::onRealTimeRequest(bool status)
{
    in_realtime_mode = status;
}

//! Processes multilayer on request. Doesn't work in real time mode.

void QuickSimController::onRunSimulationRequest()
{
    if (in_realtime_mode)
        return;
    process_multilayer(/*submit_simulation*/true);
}

//! Processes multilayer on any model change. Works only in realtime mode.

void QuickSimController::onMultiLayerChange()
{
    process_multilayer(/*submit_simulation*/in_realtime_mode);
}

//! Takes simulation results from JobManager and write into the model.

void QuickSimController::onSimulationCompleted()
{
    auto [xmin, xmax, values] = job_manager->simulationResult();
    auto data = job_model->specular_data();
    data->setAxis(ModelView::FixedBinAxisItem::create(values.size(), xmin, xmax));
    data->setContent(values);
}

//! Setups tracking of SampleModel and MaterialModel.

void QuickSimController::setup_multilayer_tracking()
{
    // Setup MaterialModel
    {
        auto on_data_change = [this](ModelView::SessionItem*, int) { onMultiLayerChange(); };
        material_model->mapper()->setOnDataChange(on_data_change, this);

        auto on_item_removed = [this](ModelView::SessionItem*, ModelView::TagRow) {
            onMultiLayerChange();
        };
        material_model->mapper()->setOnItemRemoved(on_item_removed, this);

        auto on_model_destroyed = [this](ModelView::SessionModel*) { material_model = nullptr; };
        material_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
    }

    // Setup SampleModel
    {
        auto on_data_change = [this](ModelView::SessionItem*, int) { onMultiLayerChange(); };
        sample_model->mapper()->setOnDataChange(on_data_change, this);

        auto on_item_removed = [this](ModelView::SessionItem*, ModelView::TagRow) {
            onMultiLayerChange();
        };
        sample_model->mapper()->setOnItemRemoved(on_item_removed, this);

        auto on_model_destroyed = [this](ModelView::SessionModel*) { sample_model = nullptr; };
        sample_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
    }

    onMultiLayerChange();
    job_model->sld_viewport()->update_viewport();
}

//! Constructs multislice, calculates profile and submits specular simulation.

void QuickSimController::process_multilayer(bool submit_simulation)
{
    auto multilayer = ModelView::Utils::TopItem<MultiLayerItem>(sample_model);
    auto slices = ::Utils::CreateMultiSlice(*multilayer);
    update_sld_profile(slices);
    if (submit_simulation)
        submit_specular_simulation(slices);
}

//! Calculates sld profile from slice and immediately update data items.

void QuickSimController::update_sld_profile(const multislice_t& multislice)
{
    qDebug() << "QuickSimController::update_sld_profile()";
    auto [xmin, xmax, values] =
        SpecularToySimulation::sld_profile(multislice, profile_points_count);
    auto data = job_model->sld_data();
    data->setAxis(ModelView::FixedBinAxisItem::create(values.size(), xmin, xmax));
    data->setContent(values);
}

//! Submit data to JobManager for consequent specular simulation in a separate thread.

void QuickSimController::submit_specular_simulation(const multislice_t& multislice)
{
    job_manager->requestSimulation(multislice);
}

//! Connect signals going from JobManager. Connections are made queued since signals are emitted
//! from non-GUI thread and we want to deal with widgets.

void QuickSimController::setup_jobmanager_connections()
{

    // Simulation progress is propagated from JobManager to this controller for further forwarding.
    connect(job_manager, &JobManager::progressChanged, this, &QuickSimController::progressChanged,
            Qt::QueuedConnection);

    // Notification about completed simulation from jobManager to this controller.
    connect(job_manager, &JobManager::simulationCompleted, this,
            &QuickSimController::onSimulationCompleted, Qt::QueuedConnection);
}
