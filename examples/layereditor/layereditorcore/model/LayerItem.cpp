// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerItem.h"
#include "item_constants.h"
#include "externalproperty.h"
#include <QVariant>

namespace {
QVariant material_link()
{
    return QVariant::fromValue(ModelView::ExternalProperty("Undefined", QColor(Qt::red)));
}
}

const std::string LayerItem::P_NAME = "P_NAME";
const std::string LayerItem::P_MATERIAL = "P_MATERIAL";
const std::string LayerItem::P_THICKNESS = "P_THICKNESS";

LayerItem::LayerItem() : ModelView::CompoundItem(Constants::LayerType)
{
    addProperty<ModelView::PropertyItem>(P_NAME, "Layer")->setDisplayName("Name");
    addProperty<ModelView::PropertyItem>(P_MATERIAL, material_link())->setDisplayName("Material");
    addProperty<ModelView::PropertyItem>(P_THICKNESS, 42.0)->setDisplayName("Thickness");
}
