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
    addProperty(P_COLOR, "antiquewhite")->setDisplayName("Color");
}

std::string ConnectableItem::namedColor() const
{
    return property<std::string>(P_COLOR);
}

double ConnectableItem::x() const
{
    return property<double>(P_XPOS);
}

void ConnectableItem::setX(double x)
{
    setProperty(P_XPOS, x);
}

double ConnectableItem::y() const
{
    return property<double>(P_YPOS);
}

void ConnectableItem::setY(double y)
{
    setProperty(P_YPOS, y);
}

ParticleItem::ParticleItem() : ConnectableItem(ParticleItemType)
{
    // intended to attach TransformationItem (maximum 1)
    registerTag(TagInfo(T_TRANSFORMATION, 0, 1, {TransformationItemType}), true);
}

TransformationItem::TransformationItem() : ConnectableItem(TransformationItemType)
{
    setProperty(P_COLOR, "lightseagreen");
}

} // namespace NodeEditor
