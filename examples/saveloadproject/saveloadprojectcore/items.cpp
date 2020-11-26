// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "items.h"
#include <QColor>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/externalproperty.h>

namespace
{
const std::string DemoItemType = "DemoItem";
}

using namespace ModelView;

DemoItem::DemoItem() : CompoundItem(DemoItemType)
{
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
}
