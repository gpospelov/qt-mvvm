// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphwidget.h"
#include "graphmodel.h"
#include "graphpropertywidget.h"
#include "graphwidgettoolbar.h"
#include "jobmanager.h"
#include <QBoxLayout>
#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

GraphWidget::GraphWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent), toolbar(new GraphWidgetToolBar), m_graphCanvas(new GraphCanvas),
      m_propertyWidget(new GraphPropertyWidget), m_model(nullptr), job_manager(new JobManager(this))
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    auto centralLayout = new QHBoxLayout;
    centralLayout->addWidget(m_graphCanvas, 3);
    centralLayout->addWidget(m_propertyWidget, 1);
    mainLayout->addWidget(toolbar);
    mainLayout->addLayout(centralLayout);
    setLayout(mainLayout);

    setModel(model);
    init_toolbar_connections();
    init_jobmanager_connections();
}

void GraphWidget::setModel(GraphModel* model)
{
    if (!model)
        return;
    m_model = model;
    m_propertyWidget->setModel(model);
    m_graphCanvas->setItem(Utils::TopItem<GraphViewportItem>(model));
}

//! Takes simulation results from JobManager and write into the model.

void GraphWidget::onSimulationCompleted()
{
    auto data = job_manager->simulationResult();
    if (!data.empty())
        m_model->set_data(data);
}

//! Connects signals going from toolbar.

void GraphWidget::init_toolbar_connections()
{
    // Change in amplitude is propagated from toolbar to JobManager.
    connect(toolbar, &GraphWidgetToolBar::valueChanged, job_manager,
            &JobManager::requestSimulation);

    // simulation delay factor is propagated from toolbar to JobManager
    connect(toolbar, &GraphWidgetToolBar::delayChanged, job_manager, &JobManager::setDelay);

    // cancel click is propagated from toolbar to JobManager
    connect(toolbar, &GraphWidgetToolBar::cancelPressed, job_manager,
            &JobManager::onInterruptRequest);
}

//! Connect signals going from JobManager.
//! Connections are made queued since signals are emitted from non-GUI thread and we want to
//! deal with widgets.

void GraphWidget::init_jobmanager_connections()
{
    // Simulation progress is propagated from JobManager to toolbar.
    connect(job_manager, &JobManager::progressChanged, toolbar,
            &GraphWidgetToolBar::onProgressChanged, Qt::QueuedConnection);

    // Notification about completed simulation from jobManager to GraphWidget.
    connect(job_manager, &JobManager::simulationCompleted, this,
            &GraphWidget::onSimulationCompleted, Qt::QueuedConnection);
}
