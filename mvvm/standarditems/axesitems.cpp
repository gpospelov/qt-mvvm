// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "axesitems.h"

using namespace ModelView;

BasicAxisItem::BasicAxisItem(std::string model_type) : CompoundItem(model_type) {}

FixedBinAxisItem::FixedBinAxisItem() : BasicAxisItem(Constants::FixedBinAxisType)
{
    addProperty(P_NBINS, 100)->setDisplayName("Nbins");
    addProperty(P_XMIN, 0.0)->setDisplayName("Xmin");
    addProperty(P_XMAX, 0.0)->setDisplayName("Xmax");
}
