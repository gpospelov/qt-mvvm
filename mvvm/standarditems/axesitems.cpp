// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "axesitems.h"
#include "plotitems.h"

using namespace ModelView;

BasicAxisItem::BasicAxisItem(std::string model_type) : CompoundItem(model_type) {}

void BasicAxisItem::register_min_max()
{
    addProperty(P_MIN, 0.0)->setDisplayName("Min");
    addProperty(P_MAX, 1.0)->setDisplayName("Max");
}

// --- FixedBinAxisItem ------------------------------------------------------

ViewportAxisItem::ViewportAxisItem() : BasicAxisItem(Constants::ViewportAxisType)
{
    addProperty<TextItem>(P_TITLE);
    register_min_max();
}

// --- FixedBinAxisItem ------------------------------------------------------

FixedBinAxisItem::FixedBinAxisItem() : BasicAxisItem(Constants::FixedBinAxisType)
{
    addProperty(P_NBINS, 1)->setDisplayName("Nbins");
    register_min_max();
}

std::unique_ptr<FixedBinAxisItem> FixedBinAxisItem::create(int nbins, double xmin, double xmax)
{
    auto result = std::make_unique<FixedBinAxisItem>();
    result->setItemValue(P_NBINS, nbins);
    result->setItemValue(P_MIN, xmin);
    result->setItemValue(P_MAX, xmax);
    return result;
}

std::vector<double> FixedBinAxisItem::binCenters() const
{
    std::vector<double> result;
    int nbins = getItem(P_NBINS)->data(ItemDataRole::DATA).toInt();
    double start = getItem(P_MIN)->data(ItemDataRole::DATA).toDouble();
    double end = getItem(P_MAX)->data(ItemDataRole::DATA).toDouble();
    double step = (end - start)/nbins;

    result.resize(static_cast<size_t>(nbins), 0.0);
    for(size_t i=0; i<static_cast<size_t>(nbins); ++i)
        result[i] = start + step*(i+0.5);

    return result;
}
