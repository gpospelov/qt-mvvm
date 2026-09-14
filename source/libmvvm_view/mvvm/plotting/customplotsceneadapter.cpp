// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "customplotsceneadapter.h"
#include <qcustomplot.h>
#include <QObject>
#include <memory>

using namespace ModelView;

struct CustomPlotSceneAdapter::CustomPlotSceneAdapterImpl {
    QCustomPlot* m_custom_plot{nullptr};
    std::unique_ptr<QMetaObject::Connection> m_conn_to_customplot;
    CustomPlotSceneAdapterImpl(QCustomPlot* custom_plot) : m_custom_plot(custom_plot)
    {
        m_conn_to_customplot = std::make_unique<QMetaObject::Connection>();
    }

    double toSceneX(double customplot_x) const
    {
        return m_custom_plot ? m_custom_plot->m_xAxis->coordToPixel(customplot_x) : customplot_x;
    }

    double toSceneY(double customplot_y) const
    {
        return m_custom_plot ? m_custom_plot->m_yAxis->coordToPixel(customplot_y) : customplot_y;
    }

    double fromSceneX(double scene_x) const
    {
        return m_custom_plot ? m_custom_plot->m_xAxis->pixelToCoord(scene_x) : scene_x;
    }

    double fromSceneY(double scene_y) const
    {
        return m_custom_plot ? m_custom_plot->m_yAxis->pixelToCoord(scene_y) : scene_y;
    }

    QRectF viewportRectangle() const
    {
        if (!m_custom_plot)
            return {};

        auto xrange = m_custom_plot->m_xAxis->range();
        auto yrange = m_custom_plot->m_yAxis->range();

        return QRectF(toSceneX(xrange.m_lower), toSceneY(yrange.m_upper),
                      toSceneX(xrange.m_upper) - toSceneX(xrange.m_lower),
                      toSceneY(yrange.m_lower) - toSceneY(yrange.m_upper));
    }
};

CustomPlotSceneAdapter::CustomPlotSceneAdapter(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<CustomPlotSceneAdapterImpl>(custom_plot))
{
    auto on_customplot_destroy = [this]() { p_impl->m_custom_plot = nullptr; };
    *p_impl->m_conn_to_customplot =
        QObject::connect(custom_plot, &QCustomPlot::destroyed, on_customplot_destroy);
}

CustomPlotSceneAdapter::~CustomPlotSceneAdapter()
{
    if (p_impl->m_custom_plot)
        QObject::disconnect(*p_impl->m_conn_to_customplot);
}

double CustomPlotSceneAdapter::toSceneX(double customplot_x) const
{
    return p_impl->toSceneX(customplot_x);
}

double CustomPlotSceneAdapter::toSceneY(double customplot_y) const
{
    return p_impl->toSceneY(customplot_y);
}

double CustomPlotSceneAdapter::fromSceneX(double scene_x) const
{
    return p_impl->fromSceneX(scene_x);
}

double CustomPlotSceneAdapter::fromSceneY(double scene_y) const
{
    return p_impl->fromSceneY(scene_y);
}

QRectF CustomPlotSceneAdapter::viewportRectangle() const
{
    return p_impl->viewportRectangle();
}
