// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data2ditem.h>
#include <stdexcept>

using namespace ModelView;

namespace
{
size_t total_bin_count(Data2DItem* item)
{
    if (auto xaxis = item->xAxis(); xaxis)
        if (auto yaxis = item->yAxis(); yaxis)
            return static_cast<size_t>(xaxis->size() * yaxis->size());
    return 0;
}
} // namespace

Data2DItem::Data2DItem() : CompoundItem(Constants::Data2DItemType)
{
    registerTag(TagInfo(T_XAXIS, 0, 1, {Constants::FixedBinAxisItemType}));
    registerTag(TagInfo(T_YAXIS, 0, 1, {Constants::FixedBinAxisItemType}));
    setContent(std::vector<double>()); // prevent editing in widgets, since there is no
                                       // corresponding editor
}

//! Sets axes and put data points to zero.

void Data2DItem::setAxes(std::unique_ptr<BinnedAxisItem> x_axis,
                         std::unique_ptr<BinnedAxisItem> y_axis)
{
    insert_axis(std::move(x_axis), T_XAXIS);
    insert_axis(std::move(y_axis), T_YAXIS);
    setContent(std::vector<double>(total_bin_count(this), 0.0));
}

//! Returns x-axis (nullptr if it doesn't exist).

BinnedAxisItem* Data2DItem::xAxis() const
{
    return item<BinnedAxisItem>(T_XAXIS);
}

//! Returns y-axis (nullptr if it doesn't exist).

BinnedAxisItem* Data2DItem::yAxis() const
{
    return item<BinnedAxisItem>(T_YAXIS);
}

void Data2DItem::setContent(const std::vector<double>& data)
{
    if (total_bin_count(this) != data.size())
        throw std::runtime_error("Data1DItem::setContent() -> Data doesn't match size of axis");

    setData(data);
}

//! Returns 2d vector representing 2d data.

std::vector<double> Data2DItem::content() const
{
    return data<std::vector<double>>();
}

//! Insert axis under given tag. Previous axis will be deleted and data points invalidated.

void Data2DItem::insert_axis(std::unique_ptr<BinnedAxisItem> axis, const std::string& tag)
{
    // removing previous axis
    if (auto axis = getItem(tag, 0))
        delete takeItem({tag, 0});

    insertItem(axis.release(), {tag, 0});
}
