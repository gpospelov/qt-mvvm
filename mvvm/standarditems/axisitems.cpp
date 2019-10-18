// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "axisitems.h"
#include "plottableitems.h"

using namespace ModelView;

BasicAxisItem::BasicAxisItem(std::string model_type) : CompoundItem(model_type) {}

void BasicAxisItem::register_min_max()
{
    addProperty(P_MIN, 0.0)->setDisplayName("Min");
    addProperty(P_MAX, 1.0)->setDisplayName("Max");
}

// --- ViewportAxisItem ------------------------------------------------------

ViewportAxisItem::ViewportAxisItem() : BasicAxisItem(Constants::ViewportAxisItemType)
{
    addProperty<TextItem>(P_TITLE)->setDisplayName("Title");
    register_min_max();
}

// --- BinnedAxisItem ------------------------------------------------------

BinnedAxisItem::BinnedAxisItem(std::string model_type) : BasicAxisItem(model_type)
{
    addProperty(P_NBINS, 1)->setDisplayName("Nbins");
    register_min_max();
}

int BinnedAxisItem::size() const
{
    return property(P_NBINS).toInt();
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
    int nbins = property(P_NBINS).toInt();
    double start = property(P_MIN).toDouble();
    double end = property(P_MAX).toDouble();
    double step = (end - start) / nbins;

    result.resize(static_cast<size_t>(nbins), 0.0);
    for (size_t i = 0; i < static_cast<size_t>(nbins); ++i)
        result[i] = start + step * (i + 0.5);

    return result;
}
