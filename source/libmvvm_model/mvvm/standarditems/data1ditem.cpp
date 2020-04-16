// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>

using namespace ModelView;

namespace
{
size_t total_bin_count(Data1DItem* item)
{
    auto axis = item->item<BinnedAxisItem>(Data1DItem::T_AXIS);
    return axis ? static_cast<size_t>(axis->size()) : 0;
}
} // namespace

Data1DItem::Data1DItem() : CompoundItem(Constants::Data1DItemType)
{
    registerTag(
        TagInfo(T_AXIS, 0, 1, {Constants::FixedBinAxisItemType, Constants::PointwiseAxisItemType}));
    setContent(std::vector<double>());
    setEditable(false); // prevent editing in widgets, since there is no corresponding editor
}

//! Sets axis. Bin content will be set to zero.

void Data1DItem::setAxis(std::unique_ptr<BinnedAxisItem> axis)
{
    if (auto axis = getItem(T_AXIS, 0))
        delete takeItem({T_AXIS, 0});

    insertItem(axis.release(), {T_AXIS, 0});
    setContent(std::vector<double>(total_bin_count(this), 0.0));
}

//! Sets internal data buffer to given data. If size of axis doesn't match the size of the data,
//! exception will be thrown.

void Data1DItem::setContent(const std::vector<double>& data)
{
    if (total_bin_count(this) != data.size())
        throw std::runtime_error("Data1DItem::setContent() -> Data doesn't match size of axis");

    setData(data);
}

//! Returns coordinates of bin centers.

std::vector<double> Data1DItem::binCenters() const
{
    auto axis = item<BinnedAxisItem>(T_AXIS);
    return axis ? axis->binCenters() : std::vector<double>{};
}

//! Returns values stored in bins.

std::vector<double> Data1DItem::binValues() const
{
    return data<std::vector<double>>();
}
