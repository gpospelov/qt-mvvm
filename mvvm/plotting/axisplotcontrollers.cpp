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
    QCPAxis* axis{nullptr};
    bool block_update{false};
    std::unique_ptr<QMetaObject::Connection> axis_conn;

    AxesPlotControllerPrivate(AxisPlotController* controller, QCustomPlot* plot,
                              QCPAxis* axis = nullptr)
        : controller(controller), custom_plot(plot), axis(axis)
    {
        axis_conn = std::make_unique<QMetaObject::Connection>();
    }

    //! Connects QCustomPlot signals with controller methods.
    void setConnected()
    {

        auto on_axis_range = [this](const QCPRange& newRange) {
            block_update = true;
            auto item = controller->currentItem();
            item->set_range(newRange.lower, newRange.upper);
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
        assert(axis);
        auto item = controller->currentItem();
        auto [lower, upper] = item->range();
        axis->setRange(QCPRange(lower, upper));
    }
};

AxisPlotController::AxisPlotController(QCustomPlot* custom_plot)
    : p_impl(std::make_unique<AxesPlotControllerPrivate>(this, custom_plot))
{
}

AxisPlotController::AxisPlotController(QCPAxis* axis)
    : p_impl(std::make_unique<AxesPlotControllerPrivate>(this, nullptr, axis))

{
    if (!axis)
        throw std::runtime_error("AxisPlotController: non initialized axis");
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

        // p_impl->custom_plot->replot(); FIXME
    };
    currentItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->setConnected();
}

QCPAxis* AxisPlotController::customAxis()
{
    return p_impl->axis;
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

XAxisPlotController::XAxisPlotController(QCPAxis* axis) : AxisPlotController(axis) {}

QCPAxis* XAxisPlotController::customAxis()
{
    return p_impl->axis ? p_impl->axis : customPlot()->xAxis;
}

// ----------------------------------------------------------------------------

YAxisPlotController::YAxisPlotController(QCustomPlot* cusom_plot) : AxisPlotController(cusom_plot)
{
}

YAxisPlotController::YAxisPlotController(QCPAxis* axis) : AxisPlotController(axis) {}

QCPAxis* YAxisPlotController::customAxis()
{
    return p_impl->axis ? p_impl->axis : customPlot()->yAxis;
}
