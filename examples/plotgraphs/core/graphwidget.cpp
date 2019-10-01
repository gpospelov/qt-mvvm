// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphwidget.h"
#include "graphcanvas.h"
#include "graphmodel.h"
#include "graphpropertywidget.h"
#include "graphviewportitem.h"
#include "modelutils.h"
#include <QAction>
#include <QBoxLayout>
#include <QToolBar>
#include <QToolButton>

using namespace ModelView;

GraphWidget::GraphWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent), m_toolBar(new QToolBar), m_resetViewportAction(nullptr),
      m_addGraphAction(nullptr), m_removeGraphAction(nullptr),
      m_graphCanvas(new GraphCanvas), m_propertyWidget(new GraphPropertyWidget), m_model(nullptr)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    auto centralLayout = new QHBoxLayout;

    centralLayout->addLayout(create_left_layout(), 3);
    centralLayout->addLayout(create_right_layout(), 1);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(centralLayout);

    setLayout(mainLayout);
    setModel(model);

    init_actions();
}

void GraphWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_model = model;

    m_propertyWidget->setModel(model);

    m_graphCanvas->setItem(Utils::TopItem<GraphViewportItem>(model));
}

void GraphWidget::init_actions()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    m_resetViewportAction = new QAction("Reset view", this);
    auto on_reset = [this]() {
        auto viewport = Utils::TopItem<GraphViewportItem>(m_model);
        viewport->update_viewport();
    };
    connect(m_resetViewportAction, &QAction::triggered, on_reset);

    m_addGraphAction = new QAction("Add graph", this);
    auto on_add_graph = [this]() {
        m_model->add_graph();
    };
    connect(m_resetViewportAction, &QAction::triggered, on_add_graph);

    m_removeGraphAction = new QAction("Remove graph", this);

    m_toolBar->addAction(m_resetViewportAction);
    m_toolBar->addAction(m_addGraphAction);
    m_toolBar->addAction(m_removeGraphAction);
}

GraphWidget::~GraphWidget() = default;

QBoxLayout* GraphWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_graphCanvas);
    return result;
}

QBoxLayout* GraphWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyWidget);
    return result;
}
