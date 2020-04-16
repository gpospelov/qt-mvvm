// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "quicksimeditor.h"
#include "applicationmodels.h"
#include "jobmodel.h"
#include "quicksimcontroller.h"
#include "quicksimeditortoolbar.h"
#include "styleutils.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

QuickSimEditor::QuickSimEditor(ApplicationModels* app_models, QWidget* parent)
    : QWidget(parent), app_models(app_models),
      sim_controller(new QuickSimController(app_models, this)), toolbar(new QuickSimEditorToolBar),
      spec_canvas(new ModelView::GraphCanvas)
{
    setWindowTitle(QString("Reflectivity plot"));
    auto layout = new QVBoxLayout(this);
    layout->addWidget(toolbar);
    layout->addWidget(spec_canvas);

    spec_canvas->setItem(app_models->jobModel()->specular_viewport());

    setup_toolbar_connections();
    setup_controller_connections();
}

QuickSimEditor::~QuickSimEditor() = default;

QSize QuickSimEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize QuickSimEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

//! Connects signals from toolbar.

void QuickSimEditor::setup_toolbar_connections()
{
    // Request to reset plot is propagated from toolbar to viewports.
    auto on_reset_view = [this]() { spec_canvas->update_viewport(); };
    connect(toolbar, &QuickSimEditorToolBar::resetViewRequest, on_reset_view);

    // Simulation interrupt request is propagated from toolbar to controller.
    connect(toolbar, &QuickSimEditorToolBar::cancelPressed, sim_controller,
            &QuickSimController::onInterruptRequest);

    // Request for real time mode is propagated from toobar to controller.
    connect(toolbar, &QuickSimEditorToolBar::realTimeRequest, sim_controller,
            &QuickSimController::onRealTimeRequest);

    // RUn simulation is propagated from toobar to controller.
    connect(toolbar, &QuickSimEditorToolBar::runSimulationRequest, sim_controller,
            &QuickSimController::onRunSimulationRequest);
}

//! Connects signals from controller.

void QuickSimEditor::setup_controller_connections()
{
    // Progress values propagated from controller to toolbar.
    connect(sim_controller, &QuickSimController::progressChanged, toolbar,
            &QuickSimEditorToolBar::onProgressChanged);
}
