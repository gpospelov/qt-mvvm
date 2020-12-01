// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "colormapwidget.h"
#include "colormapmodel.h"
#include "colormappropertywidget.h"
#include <QAction>
#include <QBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <mvvm/plotting/colormapcanvas.h>
#include <mvvm/standarditems/colormapviewportitem.h>

using namespace ModelView;

namespace PlotColorMap
{

ColorMapWidget::ColorMapWidget(ColorMapModel* model, QWidget* parent)
    : QWidget(parent)
    , m_toolBar(new QToolBar)
    , m_resetViewportAction(nullptr)
    , m_propertyWidget(new ColorMapPropertyWidget)
    , m_colorMapCanvas(new ColorMapCanvas)
    , m_model(nullptr)
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

    m_colorMapCanvas->setItem(model->topItem<ColorMapViewportItem>());
}

void ColorMapWidget::init_actions()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    m_resetViewportAction = new QAction("Reset view", this);
    auto on_reset = [this]() {
        auto viewport = m_model->topItem<ColorMapViewportItem>();
        viewport->setViewportToContent();
    };
    connect(m_resetViewportAction, &QAction::triggered, on_reset);

    m_toolBar->addAction(m_resetViewportAction);
}

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

} // namespace PlotColorMap
