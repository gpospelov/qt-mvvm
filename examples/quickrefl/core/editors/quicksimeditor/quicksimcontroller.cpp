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
#include "jobmodel.h"
#include "layeritems.h"
#include "materialmodel.h"
#include "materialprofile.h"
#include "quicksimutils.h"
#include "samplemodel.h"
#include "slice.h"
#include <QDebug>
#include <mvvm/model/modelutils.h>
#include <mvvm/utils/containerutils.h>
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
        auto on_data_change = [this](ModelView::SessionItem*, int) { onModelChange(); };
        material_model->mapper()->setOnDataChange(on_data_change, this);

        auto on_item_removed = [this](ModelView::SessionItem*, ModelView::TagRow) {
            onModelChange();
        };
        material_model->mapper()->setOnItemRemoved(on_item_removed, this);

        auto on_model_destroyed = [this](ModelView::SessionModel*) { material_model = nullptr; };
        material_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
    }

    // Setup SampleModel
    {
        auto on_data_change = [this](ModelView::SessionItem*, int) { onModelChange(); };
        sample_model->mapper()->setOnDataChange(on_data_change, this);

        auto on_item_removed = [this](ModelView::SessionItem*, ModelView::TagRow) {
            onModelChange();
        };
        sample_model->mapper()->setOnItemRemoved(on_item_removed, this);

        auto on_model_destroyed = [this](ModelView::SessionModel*) { sample_model = nullptr; };
        sample_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
    }
    update_sld_profile();
    auto viewport_item = ModelView::Utils::TopItem<ModelView::GraphViewportItem>(job_model);
    viewport_item->update_viewport();
}

//! Performs update of sld profile for immediate plotting.

void QuickSimController::update_sld_profile()
{
    qDebug() << "QuickSimController::update_sld_profile()";
    auto multilayer = ModelView::Utils::TopItem<MultiLayerItem>(sample_model);
    auto slices = ::Utils::CreateMultiSlice(*multilayer);

    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(slices);
    auto data_item = ModelView::Utils::TopItem<ModelView::Data1DItem>(job_model);
    data_item->setAxis(ModelView::FixedBinAxisItem::create(profile_points_count, xmin, xmax));

    auto values = ModelView::Utils::Real(MaterialProfile::CalculateProfile(slices, profile_points_count, xmin, xmax));
    data_item->setContent(values);
}

//! Submit data to JobManager for consequent specular simulation.

void QuickSimController::submit_specular_simulation()
{
    // TODO
}
