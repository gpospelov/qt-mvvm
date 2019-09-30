// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "axisplotcontrollers.h"
#include "axisitems.h"
#include "itemmapper.h"
#include "qcustomplot.h"
#include <QObject>

using namespace ModelView;

struct AxisPlotController::AxesPlotControllerPrivate {

    AxisPlotController* controller{nullptr};
    QCustomPlot* custom_plot{nullptr};
    bool block_update{false};
    std::unique_ptr<QMetaObject::Connection> axis_conn;

    AxesPlotControllerPrivate(AxisPlotController* controller, QCustomPlot* plot)
        : controller(controller), custom_plot(plot)
    {
        axis_conn = std::make_unique<QMetaObject::Connection>();
    }

    //! Connects QCustomPlot signals with controller methods.
    void setConnected()
    {

        auto on_axis_range = [this](const QCPRange& newRange) {
            block_update = true;
            auto item = controller->currentItem();
            item->setProperty(ViewportAxisItem::P_MIN, newRange.lower);
            item->setProperty(ViewportAxisItem::P_MAX, newRange.upper);
            block_update = false;
        };

        *axis_conn = QObject::connect(
            controller->customAxis(),
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), on_axis_range);
    }

    //! Disonnects QCustomPlot signals.
    void setDisconnected() { QObject::disconnect(*axis_conn); }

    //! Sets axesRange from SessionItem.
    void setAxisRangeFromItem()
    {
        auto axis = controller->customAxis();
        auto item = controller->currentItem();
        QCPRange range(item->property(ViewportAxisItem::P_MIN).toDouble(),
                       item->property(ViewportAxisItem::P_MAX).toDouble());
        axis->setRange(range);
    }
};

AxisPlotController::AxisPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<AxesPlotControllerPrivate>(this, custom_plot))
{
}

void AxisPlotController::subscribe()
{
    p_impl->setAxisRangeFromItem();

    auto on_property_change = [this](SessionItem* item, std::string name) {
        if (p_impl->block_update)
            return;

        if (name == ViewportAxisItem::P_MIN)
            customAxis()->setRangeLower(item->property(name).toDouble());

        if (name == ViewportAxisItem::P_MAX)
            customAxis()->setRangeUpper(item->property(name).toDouble());

        p_impl->custom_plot->replot();
    };
    currentItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->setConnected();
}

QCustomPlot* AxisPlotController::customPlot()
{
    return p_impl->custom_plot;
}

AxisPlotController::~AxisPlotController() = default;

// ----------------------------------------------------------------------------

XAxisPlotController::XAxisPlotController(QCustomPlot* cusom_plot) : AxisPlotController(cusom_plot)
{
}

QCPAxis* XAxisPlotController::customAxis()
{
    return customPlot()->xAxis;
}

// ----------------------------------------------------------------------------

YAxisPlotController::YAxisPlotController(QCustomPlot* cusom_plot) : AxisPlotController(cusom_plot)
{
}

QCPAxis* YAxisPlotController::customAxis()
{
    return customPlot()->yAxis;
}
