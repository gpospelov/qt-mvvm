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

GraphicsItem::GraphicsItem(const std::string& modelType) : ModelView::CompoundItem(modelType)
{
    addProperty(P_XPOS, 0.0)->setDisplayName("X");
    addProperty(P_YPOS, 0.0)->setDisplayName("Y");
    addProperty(P_COLOR, "antiquewhite");
}

ParticleItem::ParticleItem() : GraphicsItem(ParticleItemType)
{
    // intended to attach TransformationItem
    registerTag(TagInfo(T_TRANSFORMATION, 0, 1, {TransformationItemType}), true);
}

TransformationItem::TransformationItem() : GraphicsItem(TransformationItemType) {}

} // namespace NodeEditor
