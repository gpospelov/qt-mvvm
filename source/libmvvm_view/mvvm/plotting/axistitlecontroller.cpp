// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/axistitlecontroller.h"
#include "mvvm/standarditems/plottableitems.h"
#include <qcustomplot.h>
#include <stdexcept>

using namespace ModelView;

struct AxisTitleController::AxisTitleControllerImpl {
    QCPAxis* m_axis{nullptr};

    AxisTitleControllerImpl(QCPAxis* axis) : m_axis(axis)
    {
        if (!axis)
            throw std::runtime_error("AxisTitleController: axis is not initialized.");
    }

    void updateAxisFromItem(TextItem* item)
    {
        auto font = m_axis->labelFont();
        font.setPointSize(item->property<int>(TextItem::P_SIZE));
        font.setFamily(QString::fromStdString(item->property<std::string>(TextItem::P_FONT)));
        m_axis->setLabel(QString::fromStdString(item->property<std::string>(TextItem::P_TEXT)));
        m_axis->setLabelFont(font);

        m_axis->parentPlot()->replot();
    }
};

AxisTitleController::AxisTitleController(QCPAxis* axis)
    : p_impl(std::make_unique<AxisTitleControllerImpl>(axis))

{
}

AxisTitleController::~AxisTitleController() = default;

void AxisTitleController::subscribe()
{
    auto on_property_change = [this](auto, auto) { p_impl->updateAxisFromItem(currentItem()); };
    setOnPropertyChange(on_property_change);

    p_impl->updateAxisFromItem(currentItem());
}
