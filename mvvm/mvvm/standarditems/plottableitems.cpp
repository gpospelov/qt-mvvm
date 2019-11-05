// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/standarditems/plottableitems.h>

using namespace ModelView;

TextItem::TextItem() : CompoundItem(Constants::TextItemType)
{
    addProperty(P_TEXT, "")->setDisplayName("Text");
    addProperty(P_FONT, "Helvetica")->setDisplayName("Font");
    addProperty(P_SIZE, 12)->setDisplayName("Size");
}
