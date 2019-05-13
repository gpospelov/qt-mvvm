// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerItems.h"
#include "externalproperty.h"
#include "item_constants.h"
#include <QVariant>

namespace
{
QVariant material_link()
{
    return QVariant::fromValue(ModelView::ExternalProperty("Undefined", QColor(Qt::red)));
}
} // namespace

const std::string LayerItem::P_NAME = "P_NAME";
const std::string LayerItem::P_MATERIAL = "P_MATERIAL";
const std::string LayerItem::P_THICKNESS = "P_THICKNESS";

LayerItem::LayerItem() : ModelView::CompoundItem(Constants::LayerType)
{
    addProperty<ModelView::PropertyItem>(P_NAME, "Layer")->setDisplayName("Name");
    addProperty<ModelView::PropertyItem>(P_MATERIAL, material_link())->setDisplayName("Material");
    addProperty<ModelView::PropertyItem>(P_THICKNESS, 42.0)->setDisplayName("Thickness");
}

// ----------------------------------------------------------------------------

const std::string MultiLayerItem::T_LAYERS = "T_LAYERS";
const std::string MultiLayerItem::P_NREPETITIONS = "P_NREPETITIONS";

MultiLayerItem::MultiLayerItem() : ModelView::CompoundItem(Constants::MultiLayerType)
{
    addProperty<ModelView::PropertyItem>(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS,
                                                 {Constants::MultiLayerType, Constants::LayerType}),
                /*set_as_default*/ true);
}
