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

ParticleLayoutItem::ParticleLayoutItem() : ConnectableItem(ParticleLayoutItemType)
{
    // The tag is intended to attach unlimited amount of particles.
    registerTag(TagInfo(T_PARTICLE, 0, -1, {SphereItemType, CylinderItemType}));
    registerTag(TagInfo(T_LATTICE, 0, 1, {LatticeItemType}));
    setNamedColor("chartreuse");
}

std::vector<PortInfo> ParticleLayoutItem::inputPorts() const
{
    return {ParticlePort, LatticePort};
}

// ----------------------------------------------------------------------------

ParticleItem::ParticleItem(const std::string &modelType) : ConnectableItem(modelType)
{
    // The tag is intended to attach TransformationItem (maximum 1).
    registerTag(TagInfo(T_TRANSFORMATION, 0, 1, {TransformationItemType}), true);
    setNamedColor("antiquewhite");
}

std::vector<PortInfo> ParticleItem::outputPorts() const
{
    return {ParticlePort};
}

std::vector<PortInfo> ParticleItem::inputPorts() const
{
    return {TransformationPort};
}

// ----------------------------------------------------------------------------

SphereItem::SphereItem() : ParticleItem(SphereItemType)
{
    addProperty(P_RADIUS, 42.0);
}

// ----------------------------------------------------------------------------

CylinderItem::CylinderItem() : ParticleItem(CylinderItemType)
{
    addProperty(P_RADIUS, 10.0);
    addProperty(P_HEIGHT, 20.0);
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

// ----------------------------------------------------------------------------

LatticeItem::LatticeItem()
    : ConnectableItem(LatticeItemType)
{
    setNamedColor("gold");
}

std::vector<PortInfo> LatticeItem::outputPorts() const
{
    return {LatticePort};
}


} // namespace NodeEditor
