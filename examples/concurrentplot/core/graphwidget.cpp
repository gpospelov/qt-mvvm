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
      m_propertyWidget(new GraphPropertyWidget), m_model(nullptr)
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

    auto on_value_changed = [this](int value) {
        if (job_manager)
            job_manager->requestSimulation(value);
    };
    connect(toolbar, &GraphWidgetToolBar::valueChanged, on_value_changed);

    connect(job_manager.get(), &JobManager::progressChanged, toolbar,
            &GraphWidgetToolBar::onProgressChanged, Qt::QueuedConnection);
}

GraphWidget::~GraphWidget() = default;

void GraphWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_model = model;

    job_manager = std::make_unique<JobManager>(model);

    m_propertyWidget->setModel(model);

    m_graphCanvas->setItem(Utils::TopItem<GraphViewportItem>(model));
}
