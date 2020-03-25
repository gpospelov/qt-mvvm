// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "quicksimeditor.h"
#include "jobmodel.h"
#include "styleutils.h"
#include "applicationmodels.h"
#include "quicksimcontroller.h"
#include <QVBoxLayout>
#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

QuickSimEditor::QuickSimEditor(ApplicationModels* app_models, QWidget* parent)
    : QWidget(parent), app_models(app_models), job_model(std::make_unique<JobModel>()),
      sim_controller(new QuickSimController(app_models, job_model.get(), this)),
      graph_canvas(new ModelView::GraphCanvas)
{
    setWindowTitle(QString("Reflectivity plot"));
    auto layout = new QVBoxLayout;
    layout->addWidget(graph_canvas);
    setLayout(layout);

    graph_canvas->setItem(Utils::TopItem<GraphViewportItem>(job_model.get()));
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
