// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "scenewidget.h"
#include "graphicsscene.h"
#include "graphicsview.h"
#include "regionofinterestitem.h"
#include "scenemodel.h"
#include "scenepropertywidget.h"
#include "mvvm/plotting/colormapcanvas.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/colormapviewportitem.h"
#include <QAction>
#include <QBoxLayout>
#include <QToolBar>
#include <QToolButton>

using namespace ModelView;

namespace GraphicsProxy {

SceneWidget::SceneWidget(SceneModel* model, QWidget* parent)
    : QWidget(parent)
    , m_toolBar(new QToolBar)
    , m_propertyWidget(new ScenePropertyWidget)
    , m_colorMapCanvas(new ColorMapCanvas)
    , m_graphicsScene(new GraphicsScene(this))
    , m_graphicsView(new GraphicsView(m_graphicsScene, this))
    , m_model(model)
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
    m_colorMapCanvas->setItem(model->topItem<ColorMapViewportItem>());
    init_actions();

    m_graphicsScene->setContext(m_colorMapCanvas, model->topItem<RegionOfInterestItem>());
}

void SceneWidget::init_actions()
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

    m_setViewportToRoiAction = new QAction("Set to ROI", this);
    auto on_set_to_roi = [this]() {
        auto viewport = m_model->topItem<ColorMapViewportItem>();
        auto roi = m_model->topItem<RegionOfInterestItem>();
        viewport->xAxis()->set_range(roi->xLow(), roi->xUp());
        viewport->yAxis()->set_range(roi->yLow(), roi->yUp());
    };
    connect(m_setViewportToRoiAction, &QAction::triggered, on_set_to_roi);
    m_toolBar->addAction(m_setViewportToRoiAction);
}

QBoxLayout* SceneWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_graphicsView);
    return result;
}

QBoxLayout* SceneWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyWidget);
    return result;
}

} // namespace GraphicsProxy
