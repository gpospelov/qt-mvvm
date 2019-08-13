// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "plotitems.h"

using namespace ModelView;

TextItem::TextItem() : CompoundItem(Constants::TextType)
{
    addProperty(P_TEXT, "")->setDisplayName("Text");
    addProperty(P_FONT, "Helvetica")->setDisplayName("Font");
    addProperty(P_SIZE, 12)->setDisplayName("Size");
}
