// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <QObject>
#include <mvvm/plotting/axistitlecontroller.h>
#include <mvvm/plotting/customplotutils.h>
#include <mvvm/plotting/viewportaxisplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <stdexcept>

using namespace ModelView;

struct ViewportAxisPlotController::AxesPlotControllerImpl {

    ViewportAxisPlotController* m_controller{nullptr};
    QCPAxis* m_axis{nullptr};
    bool m_blockUpdate{false};
    std::unique_ptr<QMetaObject::Connection> m_axisConn;

    AxesPlotControllerImpl(ViewportAxisPlotController* controller, QCPAxis* axis)
        : m_controller(controller), m_axis(axis)
    {
        if (!axis)
            throw std::runtime_error("AxisPlotController: axis is not initialized.");
        m_axisConn = std::make_unique<QMetaObject::Connection>();
    }

    //! Connects QCustomPlot signals with controller methods.
    void setConnected()
    {

        auto on_axis_range = [this](const QCPRange& newRange) {
            m_blockUpdate = true;
            auto item = m_controller->currentItem();
            item->set_range(newRange.lower, newRange.upper);
            m_blockUpdate = false;
        };

        *m_axisConn = QObject::connect(
            m_axis, static_cast<void (QCPAxis::*)(const QCPRange&)>(&QCPAxis::rangeChanged),
            on_axis_range);
    }

    //! Disonnects QCustomPlot signals.

    void setDisconnected() { QObject::disconnect(*m_axisConn); }

    //! Sets axesRange from SessionItem.
    void setAxisRangeFromItem()
    {
        auto [lower, upper] = m_controller->currentItem()->range();
        m_axis->setRange(QCPRange(lower, upper));
    }

    //! Sets log scale from item.

    void setAxisLogScaleFromItem()
    {
        Utils::SetLogarithmicScale(m_axis, m_controller->currentItem()->is_in_log());
    }

    //! Init axis from item and setup connections.

    void init_axis()
    {
        setAxisRangeFromItem();
        setAxisLogScaleFromItem();
        setConnected();
    }

    ~AxesPlotControllerImpl() { setDisconnected(); }
};

ViewportAxisPlotController::ViewportAxisPlotController(QCPAxis* axis)
    : p_impl(std::make_unique<AxesPlotControllerImpl>(this, axis))

{
}

ViewportAxisPlotController::~ViewportAxisPlotController() = default;

void ViewportAxisPlotController::subscribe()
{
    auto on_property_change = [this](SessionItem* item, std::string name) {
        if (p_impl->m_blockUpdate)
            return;

        if (name == ViewportAxisItem::P_MIN)
            p_impl->m_axis->setRangeLower(item->property<double>(name));

        if (name == ViewportAxisItem::P_MAX)
            p_impl->m_axis->setRangeUpper(item->property<double>(name));

        if (name == ViewportAxisItem::P_IS_LOG)
            p_impl->setAxisLogScaleFromItem();

        p_impl->m_axis->parentPlot()->replot();
    };
    setOnPropertyChange(on_property_change);

    p_impl->init_axis();
}

void ViewportAxisPlotController::unsubscribe()
{
    p_impl->setDisconnected();
}
