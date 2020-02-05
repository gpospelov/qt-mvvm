// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "scenewidget.h"
#include "scenemodel.h"
#include "scenepropertywidget.h"
#include <QAction>
#include <QBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/colormapcanvas.h>
#include <mvvm/standarditems/colormapviewportitem.h>

using namespace ModelView;

SceneWidget::SceneWidget(SceneModel* model, QWidget* parent)
    : QWidget(parent), m_toolBar(new QToolBar), m_resetViewportAction(nullptr),
      m_propertyWidget(new ScenePropertyWidget), m_colorMapCanvas(new ColorMapCanvas),
      m_model(model)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    auto centralLayout = new QHBoxLayout;

    centralLayout->addLayout(create_left_layout(), 3);
    centralLayout->addLayout(create_right_layout(), 1);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(centralLayout);

    setLayout(mainLayout);

    m_propertyWidget->setModel(model);
    m_colorMapCanvas->setItem(Utils::TopItem<ColorMapViewportItem>(model));
    init_actions();
}

void SceneWidget::init_actions()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    m_resetViewportAction = new QAction("Reset view", this);
    auto on_reset = [this]() {
        auto viewport = Utils::TopItem<ColorMapViewportItem>(m_model);
        viewport->update_viewport();
    };
    connect(m_resetViewportAction, &QAction::triggered, on_reset);

    m_toolBar->addAction(m_resetViewportAction);
}

QBoxLayout* SceneWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_colorMapCanvas);
    return result;
}

QBoxLayout* SceneWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyWidget);
    return result;
}
