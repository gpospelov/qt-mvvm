// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sampleitems.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/widgets/widgetutils.h"

using namespace ModelView;

namespace NodeEditor {

ConnectableItem::ConnectableItem(const std::string& modelType) : ModelView::CompoundItem(modelType)
{
    addProperty(P_XPOS, 0.0)->setDisplayName("X");
    addProperty(P_YPOS, 0.0)->setDisplayName("Y");
    addProperty(P_COLOR, "antiquewhite");
}

std::string ConnectableItem::namedColor() const
{
    return property<std::string>(P_COLOR);
}

double ConnectableItem::xPos() const
{
    return property<double>(P_XPOS);
}

double ConnectableItem::yPos() const
{
    return property<double>(P_YPOS);
}

ParticleItem::ParticleItem() : ConnectableItem(ParticleItemType)
{
    // intended to attach TransformationItem
    registerTag(TagInfo(T_TRANSFORMATION, 0, 1, {TransformationItemType}), true);
}

TransformationItem::TransformationItem() : ConnectableItem(TransformationItemType) {}

} // namespace NodeEditor
