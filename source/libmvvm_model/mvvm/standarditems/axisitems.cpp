// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/plottableitems.h"

namespace {
const double default_axis_min = 0.0;
const double default_axis_max = 1.0;
} // namespace

using namespace ModelView;

BasicAxisItem::BasicAxisItem(const std::string& model_type) : CompoundItem(model_type) {}

void BasicAxisItem::register_min_max()
{
    addProperty(P_MIN, default_axis_min)->setDisplayName("Min");
    addProperty(P_MAX, default_axis_max)->setDisplayName("Max");
}

// --- ViewportAxisItem ------------------------------------------------------

ViewportAxisItem::ViewportAxisItem(const std::string& model_type) : BasicAxisItem(model_type)
{
    addProperty<TextItem>(P_TITLE)->setDisplayName("Title");
    register_min_max();
    addProperty(P_IS_LOG, false)->setDisplayName("log10");
}

//! Returns pair of lower, upper axis range.

std::pair<double, double> ViewportAxisItem::range() const
{
    return std::make_pair(property<double>(P_MIN), property<double>(P_MAX));
}

//! Sets lower, upper range of axis to given values.

void ViewportAxisItem::set_range(double lower, double upper)
{
    setProperty(P_MIN, lower);
    setProperty(P_MAX, upper);
}

bool ViewportAxisItem::is_in_log() const
{
    return property<bool>(P_IS_LOG);
}

// --- BinnedAxisItem ------------------------------------------------------

BinnedAxisItem::BinnedAxisItem(const std::string& model_type) : BasicAxisItem(model_type) {}

// --- FixedBinAxisItem ------------------------------------------------------

FixedBinAxisItem::FixedBinAxisItem(const std::string& model_type) : BinnedAxisItem(model_type)
{
    addProperty(P_NBINS, 1)->setDisplayName("Nbins");
    register_min_max();
}

void FixedBinAxisItem::setParameters(int nbins, double xmin, double xmax)
{
    setProperty(P_NBINS, nbins);
    setProperty(P_MIN, xmin);
    setProperty(P_MAX, xmax);
}

std::unique_ptr<FixedBinAxisItem> FixedBinAxisItem::create(int nbins, double xmin, double xmax)
{
    auto result = std::make_unique<FixedBinAxisItem>();
    result->setParameters(nbins, xmin, xmax);
    return result;
}

std::pair<double, double> FixedBinAxisItem::range() const
{
    return std::make_pair(property<double>(P_MIN), property<double>(P_MAX));
}

int FixedBinAxisItem::size() const
{
    return property<int>(P_NBINS);
}

std::vector<double> FixedBinAxisItem::binCenters() const
{
    std::vector<double> result;
    int nbins = property<int>(P_NBINS);
    double start = property<double>(P_MIN);
    double end = property<double>(P_MAX);
    double step = (end - start) / nbins;

    result.resize(static_cast<size_t>(nbins), 0.0);
    for (size_t i = 0; i < static_cast<size_t>(nbins); ++i)
        result[i] = start + step * (i + 0.5);

    return result;
}

// --- PointwiseAxisItem ------------------------------------------------------

PointwiseAxisItem::PointwiseAxisItem(const std::string& model_type) : BinnedAxisItem(model_type)
{
    // vector of points matching default xmin, xmax
    setData(std::vector<double>{default_axis_min, default_axis_max});
    setEditable(false); // prevent editing in widgets, since there is no corresponding editor
}

void PointwiseAxisItem::setParameters(const std::vector<double>& data)
{
    setData(data);
}

std::unique_ptr<PointwiseAxisItem> PointwiseAxisItem::create(const std::vector<double>& data)
{
    auto result = std::make_unique<PointwiseAxisItem>();
    result->setParameters(data);
    return result;
}

std::pair<double, double> PointwiseAxisItem::range() const
{
    auto data = binCenters();
    return binCenters().empty() ? std::make_pair(default_axis_min, default_axis_max)
                                : std::make_pair(data.front(), data.back());
}

int PointwiseAxisItem::size() const
{
    return binCenters().size();
}

std::vector<double> PointwiseAxisItem::binCenters() const
{
    return data<std::vector<double>>();
}
