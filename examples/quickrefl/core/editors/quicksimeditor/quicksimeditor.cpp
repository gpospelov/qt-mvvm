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
#include "grapheditor.h"
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
    : QWidget(parent), app_models(app_models), job_model(std::make_unique<JobModel>()),
      sim_controller(new QuickSimController(app_models, job_model.get(), this)),
      toolbar(new QuickSimEditorToolBar), sld_canvas(new ModelView::GraphCanvas),
      spec_canvas(new ModelView::GraphCanvas), tabwidget(new QTabWidget)
{
    tabwidget->addTab(sld_canvas, "SLD profile");
    tabwidget->addTab(spec_canvas, "Reflectivity");
    tabwidget->setCurrentIndex(0);
    tabwidget->setTabPosition(QTabWidget::East);

    setWindowTitle(QString("Reflectivity plot"));
    auto layout = new QVBoxLayout(this);
    layout->addWidget(toolbar);
    layout->addWidget(tabwidget);

    sld_canvas->setItem(job_model->sld_viewport());
    spec_canvas->setItem(job_model->specular_viewport());

    setup_toolbar_connections();
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

//! Connects to signals from toolbar.

void QuickSimEditor::setup_toolbar_connections()
{
    // Change in amplitude is propagated from toolbar to JobManager.
    auto on_reset_view = [this]() {
        auto viewport = tabwidget->currentIndex() == 0 ? job_model->sld_viewport()
                                                       : job_model->specular_viewport();
        viewport->update_viewport();
    };
    connect(toolbar, &QuickSimEditorToolBar::resetViewRequest, on_reset_view);
}
