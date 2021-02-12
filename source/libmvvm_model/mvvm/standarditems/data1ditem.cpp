// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/axisitems.h"
#include <stdexcept>

using namespace ModelView;

namespace {
size_t total_bin_count(Data1DItem* item)
{
    auto axis = item->item<BinnedAxisItem>(Data1DItem::T_AXIS);
    return axis ? static_cast<size_t>(axis->size()) : 0;
}
} // namespace

Data1DItem::Data1DItem() : CompoundItem(Constants::Data1DItemType)
{
    // prevent editing in widgets, since there is no corresponding editor
    addProperty(P_VALUES, std::vector<double>())->setDisplayName("Values")->setEditable(false);

    addProperty(P_ERRORS, std::vector<double>())->setDisplayName("Errors")->setEditable(false);

    registerTag(
        TagInfo(T_AXIS, 0, 1, {Constants::FixedBinAxisItemType, Constants::PointwiseAxisItemType}),
        true);
}

//! Sets axis. Bin content will be set to zero.

// void Data1DItem::setAxis(std::unique_ptr<BinnedAxisItem> axis)
//{
//    // we disable possibility to re-create axis to facilitate undo/redo

//    if (getItem(T_AXIS, 0))
//        throw std::runtime_error("Axis was already set. Currently we do not support axis change");

//    insertItem(axis.release(), {T_AXIS, 0});
//    setValues(std::vector<double>(total_bin_count(this), 0.0));
//}

//! Returns coordinates of bin centers.

std::vector<double> Data1DItem::binCenters() const
{
    auto axis = item<BinnedAxisItem>(T_AXIS);
    return axis ? axis->binCenters() : std::vector<double>{};
}

//! Sets internal data buffer to given data. If size of axis doesn't match the size of the data,
//! exception will be thrown.

void Data1DItem::setValues(const std::vector<double>& data)
{
    if (total_bin_count(this) != data.size())
        throw std::runtime_error("Data1DItem::setValues() -> Data doesn't match size of axis");

    setProperty(P_VALUES, data);
}

//! Returns values stored in bins.

std::vector<double> Data1DItem::binValues() const
{
    return property<std::vector<double>>(P_VALUES);
}

//! Sets errors on values in bins.

void Data1DItem::setErrors(const std::vector<double>& errors)
{
    if (total_bin_count(this) != errors.size())
        throw std::runtime_error("Data1DItem::setErrors() -> Data doesn't match size of axis");

    setProperty(P_ERRORS, errors);
}

//! Returns value errors stored in bins.

std::vector<double> Data1DItem::binErrors() const
{
    return property<std::vector<double>>(P_ERRORS);
}
