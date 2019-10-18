// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "colormapwidget.h"
#include "colormapmodel.h"
#include "colormappropertywidget.h"
#include "modelutils.h"
#include "colormapcanvas.h"
#include <QAction>
#include <QBoxLayout>
#include <QDebug>
#include <QToolBar>
#include <QToolButton>

using namespace ModelView;

ColorMapWidget::ColorMapWidget(ColorMapModel* model, QWidget* parent)
    : QWidget(parent), m_toolBar(new QToolBar), m_resetViewportAction(nullptr),
      m_addPlotAction(nullptr), m_removePlotAction(nullptr),
      m_propertyWidget(new ColorMapPropertyWidget), m_colorMapCanvas(new ColorMapCanvas), m_model(nullptr)
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

void ColorMapWidget::setModel(ColorMapModel* model)
{
    if (!model)
        return;

    m_model = model;

    m_propertyWidget->setModel(model);
}

void ColorMapWidget::init_actions()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    m_resetViewportAction = new QAction("Reset view", this);
    auto on_reset = []() { qDebug() << "On reset"; };
    connect(m_resetViewportAction, &QAction::triggered, on_reset);

    m_addPlotAction = new QAction("Add plot", this);
    auto on_add_plot = []() { qDebug() << "Add plot"; };
    connect(m_addPlotAction, &QAction::triggered, on_add_plot);

    m_removePlotAction = new QAction("Remove plot", this);
    auto on_remove_plot = []() { qDebug() << "Remove plot"; };
    connect(m_removePlotAction, &QAction::triggered, on_remove_plot);

    m_toolBar->addAction(m_resetViewportAction);
    m_toolBar->addAction(m_addPlotAction);
    m_toolBar->addAction(m_removePlotAction);
}

ColorMapWidget::~ColorMapWidget() = default;

QBoxLayout* ColorMapWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_colorMapCanvas);
    return result;
}

QBoxLayout* ColorMapWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyWidget);
    return result;
}
