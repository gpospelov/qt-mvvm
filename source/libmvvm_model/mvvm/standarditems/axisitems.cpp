// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/plottableitems.h>

namespace
{
const double default_axis_min = 0.0;
const double default_axis_max = 1.0;
} // namespace

using namespace ModelView;

BasicAxisItem::BasicAxisItem(const std::string& model_type) : CompoundItem(model_type) {}

void BasicAxisItem::register_min_max()
{
    addProperty(P_MIN, default_axis_min)->setDisplayName("Min")->setLimits(RealLimits::limitless());
    addProperty(P_MAX, default_axis_max)->setDisplayName("Max")->setLimits(RealLimits::limitless());
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
    return std::make_pair(property(P_MIN).value<double>(), property(P_MAX).value<double>());
}

//! Sets lower, upper range of axis to given values.

void ViewportAxisItem::set_range(double lower, double upper)
{
    setProperty(P_MIN, lower);
    setProperty(P_MAX, upper);
}

bool ViewportAxisItem::is_in_log() const
{
    return property(P_IS_LOG).value<bool>();
}

// --- BinnedAxisItem ------------------------------------------------------

BinnedAxisItem::BinnedAxisItem(const std::string& model_type) : BasicAxisItem(model_type)
{
    addProperty(P_NBINS, 1)->setDisplayName("Nbins");
    register_min_max();
}

std::pair<double, double> BinnedAxisItem::range() const
{
    return std::make_pair(property(P_MIN).value<double>(), property(P_MAX).value<double>());
}

int BinnedAxisItem::size() const
{
    return property(P_NBINS).value<int>();
}

// --- FixedBinAxisItem ------------------------------------------------------

FixedBinAxisItem::FixedBinAxisItem() : BinnedAxisItem(Constants::FixedBinAxisItemType) {}

std::unique_ptr<FixedBinAxisItem> FixedBinAxisItem::create(int nbins, double xmin, double xmax)
{
    auto result = std::make_unique<FixedBinAxisItem>();
    result->setProperty(P_NBINS, nbins);
    result->setProperty(P_MIN, xmin);
    result->setProperty(P_MAX, xmax);
    return result;
}

std::vector<double> FixedBinAxisItem::binCenters() const
{
    std::vector<double> result;
    int nbins = property(P_NBINS).value<int>();
    double start = property(P_MIN).value<double>();
    double end = property(P_MAX).value<double>();
    double step = (end - start) / nbins;

    result.resize(static_cast<size_t>(nbins), 0.0);
    for (size_t i = 0; i < static_cast<size_t>(nbins); ++i)
        result[i] = start + step * (i + 0.5);

    return result;
}
