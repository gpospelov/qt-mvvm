// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/colormapviewportplotcontroller.h"
#include "mvvm/plotting/colormapplotcontroller.h"
#include "mvvm/plotting/colorscaleplotcontroller.h"
#include "mvvm/plotting/viewportaxisplotcontroller.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/colormapitem.h"
#include "mvvm/standarditems/colormapviewportitem.h"
#include <qcustomplot.h>

using namespace ModelView;

struct ColorMapViewportPlotController::ColorMapViewportPlotControllerImpl {
    ColorMapViewportPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPColorScale* m_colorScale{nullptr};
    std::unique_ptr<ViewportAxisPlotController> m_xAxisController;
    std::unique_ptr<ViewportAxisPlotController> m_yAxisController;
    std::unique_ptr<ColorScalePlotController> m_colorScaleController;
    std::unique_ptr<ColorMapPlotController> m_colorMapController;

    ColorMapViewportPlotControllerImpl(ColorMapViewportPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot), m_colorScale(new QCPColorScale(m_customPlot))
    {
        m_xAxisController = std::make_unique<ViewportAxisPlotController>(m_customPlot->xAxis);
        m_yAxisController = std::make_unique<ViewportAxisPlotController>(m_customPlot->yAxis);
        m_colorScaleController = std::make_unique<ColorScalePlotController>(m_colorScale);
        m_colorMapController = std::make_unique<ColorMapPlotController>(m_customPlot, m_colorScale);
    }

    ColorMapViewportItem* viewportItem() { return m_self->currentItem(); }

    //! Setup controller components.

    void setup_components()
    {
        auto viewport = viewportItem();
        m_xAxisController->setItem(viewport->xAxis());
        m_yAxisController->setItem(viewport->yAxis());
        m_colorScaleController->setItem(viewport->zAxis());
        auto colormap_item = viewportItem()->item<ColorMapItem>(ColorMapViewportItem::T_ITEMS);
        m_colorMapController->setItem(colormap_item);
        viewportItem()->setViewportToContent();
    }

    void unsubscribe_components()
    {
        m_xAxisController->setItem(nullptr);
        m_yAxisController->setItem(nullptr);
        m_colorScaleController->setItem(nullptr);
        m_colorMapController->setItem(nullptr);
    }
};

ColorMapViewportPlotController::ColorMapViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<ColorMapViewportPlotControllerImpl>(this, custom_plot))
{
}

void ColorMapViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](SessionItem*, TagRow) { p_impl->setup_components(); };
    setOnItemInserted(on_item_inserted);

    p_impl->setup_components();
}

void ColorMapViewportPlotController::unsubscribe()
{
    p_impl->unsubscribe_components();
}

ColorMapViewportPlotController::~ColorMapViewportPlotController() = default;
