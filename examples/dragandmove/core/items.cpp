// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "items.h"
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/externalproperty.h>
#include "item_constants.h"
#include <QColor>

using namespace ModelView;

DemoItem::DemoItem() : CompoundItem(::Constants::DemoItemType)
{
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
}

DemoContainerItem::DemoContainerItem() : CompoundItem(::Constants::DemoContainerItemType)
{
    registerTag(TagInfo::universalTag(T_ITEMS, {::Constants::DemoItemType}), /*set_default*/ true);
}
