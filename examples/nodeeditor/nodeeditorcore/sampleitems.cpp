// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sampleitems.h"
#include <QColor>

using namespace ModelView;

namespace NodeEditor {

// ----------------------------------------------------------------------------

ParticleItem::ParticleItem() : ConnectableItem(ParticleItemType)
{
    // intended to attach TransformationItem (maximum 1)
    registerTag(TagInfo(T_TRANSFORMATION, 0, 1, {TransformationItemType}), true);
    setNamedColor("antiquewhite");
}

std::vector<PortInfo> ParticleItem::inputPorts() const
{
    return {TransformationPort};
}

// ----------------------------------------------------------------------------

TransformationItem::TransformationItem() : ConnectableItem(TransformationItemType)
{
    setNamedColor("lightseagreen");
}

std::vector<PortInfo> TransformationItem::outputPorts() const
{
    return {TransformationPort};
}

} // namespace NodeEditor
