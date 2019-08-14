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
    addProperty(P_MAX, 0.0)->setDisplayName("Max");
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
    addProperty(P_NBINS, 100)->setDisplayName("Nbins");
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
