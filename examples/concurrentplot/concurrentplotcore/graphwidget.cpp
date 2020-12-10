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
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

GraphWidget::GraphWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent)
    , m_toolbar(new GraphWidgetToolBar)
    , m_graphCanvas(new GraphCanvas)
    , m_propertyWidget(new GraphPropertyWidget)
    , m_model(nullptr)
    , m_jobManager(new JobManager(this))
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    auto centralLayout = new QHBoxLayout;
    centralLayout->addWidget(m_graphCanvas, 3);
    centralLayout->addWidget(m_propertyWidget, 1);
    mainLayout->addWidget(m_toolbar);
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
    m_graphCanvas->setItem(model->topItem<GraphViewportItem>());
}

//! Takes simulation results from JobManager and write into the model.

void GraphWidget::onSimulationCompleted()
{
    auto data = m_jobManager->simulationResult();
    if (!data.empty())
        m_model->set_data(data);
}

//! Connects signals going from toolbar.

void GraphWidget::init_toolbar_connections()
{
    // Change in amplitude is propagated from toolbar to JobManager.
    connect(m_toolbar, &GraphWidgetToolBar::valueChanged, m_jobManager,
            &JobManager::requestSimulation);

    // simulation delay factor is propagated from toolbar to JobManager
    connect(m_toolbar, &GraphWidgetToolBar::delayChanged, m_jobManager, &JobManager::setDelay);

    // cancel click is propagated from toolbar to JobManager
    connect(m_toolbar, &GraphWidgetToolBar::cancelPressed, m_jobManager,
            &JobManager::onInterruptRequest);
}

//! Connect signals going from JobManager.
//! Connections are made queued since signals are emitted from non-GUI thread and we want to
//! deal with widgets.

void GraphWidget::init_jobmanager_connections()
{
    // Simulation progress is propagated from JobManager to toolbar.
    connect(m_jobManager, &JobManager::progressChanged, m_toolbar,
            &GraphWidgetToolBar::onProgressChanged, Qt::QueuedConnection);

    // Notification about completed simulation from jobManager to GraphWidget.
    connect(m_jobManager, &JobManager::simulationCompleted, this,
            &GraphWidget::onSimulationCompleted, Qt::QueuedConnection);
}
