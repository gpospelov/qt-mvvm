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
      sld_canvas(new GraphEditor), spec_canvas(new GraphEditor), tabwidget(new QTabWidget)
{
    tabwidget->addTab(sld_canvas, "SLD profile");
    tabwidget->addTab(spec_canvas, "Reflectivity");
    tabwidget->setCurrentIndex(0);
    tabwidget->setTabPosition(QTabWidget::East);

    setWindowTitle(QString("Reflectivity plot"));
    auto layout = new QVBoxLayout(this);
    layout->addWidget(tabwidget);

    sld_canvas->setItem(job_model->sld_viewport());
    spec_canvas->setItem(job_model->specular_viewport());
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
