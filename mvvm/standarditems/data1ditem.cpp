// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "data1ditem.h"

using namespace ModelView;

Data1DItem::Data1DItem() : CompoundItem(Constants::Data1DItemType)
{
    TagInfo tagInfo(T_AXIS, 0, 1, {Constants::FixedBinAxisType});
    registerTag(tagInfo, /*set_as_default*/true);
}
