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
#include "mvvm/plotting/graphcanvas.h"
#include "mvvm/standarditems/graphviewportitem.h"
#include <QAction>
#include <QBoxLayout>
#include <QToolBar>
#include <QToolButton>

using namespace ModelView;

namespace PlotGraphs {

GraphWidget::GraphWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent)
    , m_toolBar(new QToolBar)
    , m_graphCanvas(new GraphCanvas)
    , m_propertyWidget(new GraphPropertyWidget)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    auto centralLayout = new QHBoxLayout;

    centralLayout->addLayout(createLeftLayout(), 3);
    centralLayout->addLayout(createRightLayout(), 1);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(centralLayout);

    setLayout(mainLayout);
    setModel(model);

    initActions();
}

void GraphWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_model = model;

    m_propertyWidget->setModel(model);

    m_graphCanvas->setItem(model->topItem<GraphViewportItem>());
}

void GraphWidget::initActions()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    m_resetViewportAction = new QAction("Reset view", this);
    auto on_reset = [this]() {
        auto viewport = m_model->topItem<GraphViewportItem>();
        viewport->setViewportToContent(0.0, 0.1, 0.0, 0.1);
    };
    connect(m_resetViewportAction, &QAction::triggered, on_reset);

    m_addGraphAction = new QAction("Add graph", this);
    auto on_add_graph = [this]() { m_model->addGraph(); };
    connect(m_addGraphAction, &QAction::triggered, on_add_graph);

    m_removeGraphAction = new QAction("Remove graph", this);
    auto on_remove_graph = [this]() { m_model->removeGraph(); };
    connect(m_removeGraphAction, &QAction::triggered, on_remove_graph);

    m_toolBar->addAction(m_resetViewportAction);
    m_toolBar->addAction(m_addGraphAction);
    m_toolBar->addAction(m_removeGraphAction);

    m_toolBar->addSeparator();

    auto undo_action = new QAction("Undo", this);
    connect(undo_action, &QAction::triggered, [this]() { m_model->undo(); });
    m_toolBar->addAction(undo_action);

    auto redo_action = new QAction("Redo", this);
    connect(redo_action, &QAction::triggered, [this]() { m_model->redo(); });
    m_toolBar->addAction(redo_action);
}

GraphWidget::~GraphWidget() = default;

QBoxLayout* GraphWidget::createLeftLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_graphCanvas);
    return result;
}

QBoxLayout* GraphWidget::createRightLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyWidget);
    return result;
}

} // namespace PlotGraphs
