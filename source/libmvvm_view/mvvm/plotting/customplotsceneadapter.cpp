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

using namespace ModelView;

struct CustomPlotSceneAdapter::CustomPlotSceneAdapterImpl {
    QCustomPlot* custom_plot{nullptr};
    std::unique_ptr<QMetaObject::Connection> conn_to_customplot;
    CustomPlotSceneAdapterImpl(QCustomPlot* custom_plot) : custom_plot(custom_plot)
    {
        conn_to_customplot = std::make_unique<QMetaObject::Connection>();
    }

    double toSceneX(double customplot_x) const
    {
        return custom_plot ? custom_plot->xAxis->coordToPixel(customplot_x) : customplot_x;
    }

    double toSceneY(double customplot_y) const
    {
        return custom_plot ? custom_plot->yAxis->coordToPixel(customplot_y) : customplot_y;
    }

    double fromSceneX(double scene_x) const
    {
        return custom_plot ? custom_plot->xAxis->pixelToCoord(scene_x) : scene_x;
    }

    double fromSceneY(double scene_y) const
    {
        return custom_plot ? custom_plot->yAxis->pixelToCoord(scene_y) : scene_y;
    }

    QRectF viewportRectangle() const
    {
        if (!custom_plot)
            return {};

        auto xrange = custom_plot->xAxis->range();
        auto yrange = custom_plot->yAxis->range();

        return QRectF(toSceneX(xrange.lower), toSceneY(yrange.upper),
                      toSceneX(xrange.upper) - toSceneX(xrange.lower),
                      toSceneY(yrange.lower) - toSceneY(yrange.upper));
    }
};

CustomPlotSceneAdapter::CustomPlotSceneAdapter(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<CustomPlotSceneAdapterImpl>(custom_plot))
{
    auto on_customplot_destroy = [this]() { p_impl->custom_plot = nullptr; };
    *p_impl->conn_to_customplot =
        QObject::connect(custom_plot, &QCustomPlot::destroyed, on_customplot_destroy);
}

CustomPlotSceneAdapter::~CustomPlotSceneAdapter()
{
    if (p_impl->custom_plot)
        QObject::disconnect(*p_impl->conn_to_customplot);
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
