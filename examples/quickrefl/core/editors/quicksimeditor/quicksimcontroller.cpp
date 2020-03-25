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
#include "materialmodel.h"
#include "samplemodel.h"
#include <QDebug>
#include <mvvm/signals/modelmapper.h>

using namespace ModelView;

QuickSimController::QuickSimController(ApplicationModels* app_models, JobModel* job_model,
                                       QObject* parent)
    : QObject(parent), sample_model(app_models->sampleModel()),
      material_model(app_models->materialModel()), job_model(job_model)
{
    setup_models_tracking();
}

QuickSimController::~QuickSimController()
{
    if (material_model)
        material_model->mapper()->unsubscribe(this);
    if (sample_model)
        sample_model->mapper()->unsubscribe(this);
}

//! Submits simulation job.

void QuickSimController::onModelChange()
{
    qDebug() << "onModelChange";
    update_sld_profile();
    submit_specular_simulation();
}

//! Setups tracking of SampleModel and MaterialModel.

void QuickSimController::setup_models_tracking()
{
    // Setup MaterialModel
    {
        auto on_data_change = [this](SessionItem*, int) { onModelChange(); };
        material_model->mapper()->setOnDataChange(on_data_change, this);

        auto on_item_removed = [this](SessionItem*, TagRow) { onModelChange(); };
        material_model->mapper()->setOnItemRemoved(on_item_removed, this);

        auto on_model_destroyed = [this](SessionModel*) { material_model = nullptr; };
        material_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
    }

    // Setup SampleModel
    {
        auto on_data_change = [this](SessionItem*, int) { onModelChange(); };
        sample_model->mapper()->setOnDataChange(on_data_change, this);

        auto on_item_removed = [this](SessionItem*, TagRow) { onModelChange(); };
        sample_model->mapper()->setOnItemRemoved(on_item_removed, this);

        auto on_model_destroyed = [this](SessionModel*) { sample_model = nullptr; };
        sample_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
    }

}

//! Performs update of sld profile for immediate plotting.

void QuickSimController::update_sld_profile()
{
    // TODO
}

//! Submit data to JobManager for consequent specular simulation.

void QuickSimController::submit_specular_simulation()
{
    // TODO
}
