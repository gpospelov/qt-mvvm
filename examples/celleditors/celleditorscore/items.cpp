// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "items.h"
#include "item_constants.h"
#include <QColor>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/externalproperty.h>
#include <QDebug>


using namespace ModelView;

DemoPropertiesItem::DemoPropertiesItem() : CompoundItem(::Constants::DemoPropertiesType)
{
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    RealLimits lim = RealLimits::limited(-50, 50);
    qDebug() << "qqq" << lim.lowerLimit() << lim.upperLimit();
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer")->setLimits(lim);
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double")->setLimits(RealLimits::limited(-41.0, 43.0));
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");

    auto combo = ComboProperty::createFrom({"option 1", "option 2", "option 3"});
    addProperty(P_COMBO_PROPERTY, combo)->setDisplayName("Combo");

    ExternalProperty ext_prop("Gold", QColor(Qt::darkYellow), "some id");
    addProperty(P_EXTERNAL_PROPERTY, ext_prop)->setDisplayName("External");
}
