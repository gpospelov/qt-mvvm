// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/data2dplotcontroller.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/data2ditem.h"
#include <qcustomplot.h>
#include <algorithm>
#include <stdexcept>

using namespace ModelView;

namespace {
//! Returns QCPRange of axis.
QCPRange qcpRange(const BinnedAxisItem* axis)
{
    auto centers = axis->binCenters(); // QCPColorMapData expects centers of bin
    return centers.empty() ? QCPRange() : QCPRange(centers.front(), centers.back());
}
} // namespace

struct Data2DPlotController::Data2DPlotControllerImpl {
    Data2DPlotController* master{nullptr};
    QCPColorMap* color_map{nullptr};
    Data2DPlotControllerImpl(Data2DPlotController* master, QCPColorMap* color_map)
        : master(master), color_map(color_map)
    {
        if (!color_map)
            throw std::runtime_error("Uninitialised colormap in Data2DPlotController");
    }

    Data2DItem* dataItem() { return master->currentItem(); }

    void update_data_points()
    {
        reset_colormap();

        if (auto data_item = dataItem(); data_item) {
            auto xAxis = data_item->xAxis();
            auto yAxis = data_item->yAxis();
            if (xAxis && yAxis) {
                const int nbinsx = xAxis->size();
                const int nbinsy = yAxis->size();

                color_map->data()->setSize(nbinsx, nbinsy);
                color_map->data()->setRange(qcpRange(xAxis), qcpRange(yAxis));

                auto values = data_item->content();
                for (int ix = 0; ix < nbinsx; ++ix)
                    for (int iy = 0; iy < nbinsy; ++iy)
                        color_map->data()->setCell(ix, iy,
                                                   values[static_cast<size_t>(ix + iy * nbinsx)]);

                auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
                color_map->setDataRange(QCPRange(*min, *max));
            }
        }
        color_map->parentPlot()->replot();
    }

    void reset_colormap() { color_map->data()->clear(); }
};

Data2DPlotController::Data2DPlotController(QCPColorMap* color_map)
    : p_impl(std::make_unique<Data2DPlotControllerImpl>(this, color_map))
{
}

Data2DPlotController::~Data2DPlotController() = default;

void Data2DPlotController::subscribe()
{
    auto on_property_change = [this](SessionItem*, const std::string& name) {
        if (name == Data2DItem::P_VALUES)
            p_impl->update_data_points();
    };
    setOnPropertyChange(on_property_change);

    p_impl->update_data_points();
}

void Data2DPlotController::unsubscribe()
{
    p_impl->reset_colormap();
}
