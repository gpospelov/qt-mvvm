// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/pencontroller.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/standarditems/plottableitems.h"
#include <qcustomplot.h>
#include <stdexcept>

using namespace ModelView;

namespace {
//! Returns Qt pen style from current ComboProperty index.
Qt::PenStyle getQtPenFromComboIndex(const ComboProperty& combo)
{
    // our ComboProperty for pens coincide with Qt definition
    return static_cast<Qt::PenStyle>(combo.currentIndex());
}
} // namespace

struct PenController::PenControllerImpl {
    QCPGraph* m_graph{nullptr};
    PenControllerImpl(QCPGraph* graph) : m_graph(graph)
    {
        if (!m_graph)
            throw std::runtime_error("Error in PenController: uninitialised graph.");
    }

    void update_graph_from_item(PenItem* item)
    {
        QColor color(QString::fromStdString(item->colorName()));
        auto pencombo = item->property<ComboProperty>(PenItem::P_STYLE);
        auto penwidth = item->property<int>(PenItem::P_WIDTH);

        QPen pen;
        pen.setColor(color);
        pen.setStyle(getQtPenFromComboIndex(pencombo));
        pen.setWidth(penwidth);
        m_graph->setPen(pen);

        m_graph->parentPlot()->replot();
    }
};

PenController::PenController(QCPGraph* graph) : p_impl(std::make_unique<PenControllerImpl>(graph))
{
}

PenController::~PenController() = default;

void PenController::subscribe()
{
    auto on_property_change = [this](auto, auto) { p_impl->update_graph_from_item(currentItem()); };
    setOnPropertyChange(on_property_change);

    p_impl->update_graph_from_item(currentItem());
}
