// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "data2dplotcontroller.h"
#include "axisitems.h"
#include "data2ditem.h"
#include "qcustomplot.h"

using namespace ModelView;

namespace
{
//! Returns QCPRange of axis.
QCPRange qcpRange(const BinnedAxisItem* axis)
{
    auto centers = axis->binCenters(); // QCPColorMapData expects centers of bin
    return centers.empty() ? QCPRange() : QCPRange(centers.front(), centers.back());
}
} // namespace

struct Data2DPlotController::Data2DPlotControllerPrivate {
    Data2DPlotController* master{nullptr};
    QCPColorMap* color_map{nullptr};
    Data2DPlotControllerPrivate(Data2DPlotController* master, QCPColorMap* color_map)
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

            }
        }
        color_map->parentPlot()->replot();
    }

    void reset_colormap() { color_map->data()->clear(); }
};

Data2DPlotController::Data2DPlotController(QCPColorMap* color_map)
    : p_impl(std::make_unique<Data2DPlotControllerPrivate>(this, color_map))
{
}

Data2DPlotController::~Data2DPlotController() = default;

void Data2DPlotController::subscribe()
{
    auto on_data_change = [this](SessionItem*, int) { p_impl->update_data_points(); };
    currentItem()->mapper()->setOnDataChange(on_data_change, this);

    p_impl->update_data_points();
}

void Data2DPlotController::unsubscribe()
{
    p_impl->reset_colormap();
}
