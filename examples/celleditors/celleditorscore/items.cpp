// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "items.h"
#include "item_constants.h"

const std::string DemoPropertiesItem::P_BOOL_PROPERTY = "P_BOOL_PROPERTY";
const std::string DemoPropertiesItem::P_INTEGER_PROPERTY = "P_INTEGER_PROPERTY";
const std::string DemoPropertiesItem::P_DOUBLE_PROPERTY = "P_DOUBLE_PROPERTY";

DemoPropertiesItem::DemoPropertiesItem() : CompoundItem(Constants::DemoPropertiesType)
{
    addProperty<ModelView::PropertyItem>(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty<ModelView::PropertyItem>(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty<ModelView::PropertyItem>(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
}
