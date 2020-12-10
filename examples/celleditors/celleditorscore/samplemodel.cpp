// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "item_constants.h"
#include <QColor>
#include <mvvm/editors/editor_constants.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/reallimits.h>

using namespace ModelView;

namespace CellEditors
{

DemoPropertiesItem::DemoPropertiesItem() : CompoundItem(::Constants::DemoPropertiesType)
{
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool")->setToolTip("tooltip");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1234)
        ->setDisplayName("Double")
        ->setLimits(RealLimits::limitless());
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");

    auto combo = ComboProperty::createFrom({"option 1", "option 2", "option 3"});
    addProperty(P_COMBO_PROPERTY, combo)->setDisplayName("Combo");

    addProperty(P_SELECTABLE_COMBO_PROPERTY, combo)
        ->setDisplayName("Selectable")
        ->setEditorType(ModelView::Constants::SelectableComboPropertyEditorType);

    ExternalProperty ext_prop("Gold", QColor(Qt::darkYellow), "some id");
    addProperty(P_EXTERNAL_PROPERTY, ext_prop)->setDisplayName("External");
}

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    auto catalogue = std::make_unique<ModelView::ItemCatalogue>();
    catalogue->registerItem<DemoPropertiesItem>();

    setItemCatalogue(std::move(catalogue));
}

} // namespace CellEditors
