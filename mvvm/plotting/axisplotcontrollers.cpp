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

using namespace ModelView;

struct AxisPlotController::AxesPlotControllerPrivate {

    AxisPlotController* m_controller{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    bool m_block_update{false};
    std::unique_ptr<QMetaObject::Connection> axis_conn;

    AxesPlotControllerPrivate(AxisPlotController* controller, QCustomPlot* plot)
        : m_controller(controller), m_customPlot(plot)
    {
        axis_conn = std::make_unique<QMetaObject::Connection>();
    }

    void setConnected()
    {

        auto on_axis_range = [this](const QCPRange& newRange) {
            m_block_update = true;
            auto item = m_controller->currentItem();
            item->setProperty(ViewportAxisItem::P_MIN, newRange.lower);
            item->setProperty(ViewportAxisItem::P_MAX, newRange.upper);
            m_block_update = false;
        };

        *axis_conn = connect(
            m_controller->customAxis(),
            static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged), on_axis_range);
    }

    void setDisconnected() { QObject::disconnect(*axis_conn); }
};

AxisPlotController::AxisPlotController(QCustomPlot* custom_plot, QObject* parent)
    : ItemController(parent), p_impl(std::make_unique<AxesPlotControllerPrivate>(this, custom_plot))
{
}

void AxisPlotController::subscribe()
{
    auto on_property_change = [this](SessionItem* item, std::string name) {
        if (p_impl->m_block_update)
            return;

        if (name == ViewportAxisItem::P_MIN)
            customAxis()->setRangeLower(item->property(name).toDouble());

        if (name == ViewportAxisItem::P_MAX)
            customAxis()->setRangeUpper(item->property(name).toDouble());
    };
    axisItem()->mapper()->setOnPropertyChange(on_property_change, this);

    p_impl->setConnected();
}

ViewportAxisItem* AxisPlotController::axisItem()
{
    return dynamic_cast<ViewportAxisItem*>(currentItem());
}

QCustomPlot* AxisPlotController::customPlot()
{
    return p_impl->m_customPlot;
}

AxisPlotController::~AxisPlotController() = default;

// ----------------------------------------------------------------------------

XAxisPlotController::XAxisPlotController(QCustomPlot* cusom_plot, QObject* parent)
    : AxisPlotController(cusom_plot, parent)
{
}

QCPAxis* XAxisPlotController::customAxis()
{
    return customPlot()->xAxis;
}

// ----------------------------------------------------------------------------

YAxisPlotController::YAxisPlotController(QCustomPlot* cusom_plot, QObject* parent)
    : AxisPlotController(cusom_plot, parent)
{
}

QCPAxis* YAxisPlotController::customAxis()
{
    return customPlot()->yAxis;
}
