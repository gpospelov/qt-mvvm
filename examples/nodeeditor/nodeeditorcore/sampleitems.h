// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_SAMPLEITEMS_H
#define NODEEDITORCORE_SAMPLEITEMS_H

//! @file sampleitems.h
//! Classes to represent content of node editor.

#include "connectableitem.h"

namespace NodeEditor {

const std::string SphereItemType = "Sphere";
const std::string CylinderItemType = "Cylinder";
const std::string TransformationItemType = "Transformation";
const std::string ParticleLayoutItemType = "ParticleLayout";
const std::string LatticeItemType = "Lattice";

//! Represents layout box on the graphics scene.
//! It has two input ports: one to connect an arbitrary amount of particles of various shape,
//! another to connect a singel lattice. Doesn't have output port (i.e. the top level item in
//! the node editor hierarchy).

class ParticleLayoutItem : public ConnectableItem {
public:
    static inline const std::string T_PARTICLE = "Particle";
    static inline const std::string T_LATTICE = "Lattice";
    ParticleLayoutItem();

    std::vector<PortInfo> inputPorts() const override;
};

//! Base class for particle presentation on the graphics scene.
//! Has single input port to connect single transformation item, and single output.
//! Can be connected with ParticleLayoutItem.

class ParticleItem : public ConnectableItem {
public:
    static inline const std::string T_TRANSFORMATION = "Transformation";
    ParticleItem(const std::string& modelType);

    std::vector<PortInfo> outputPorts() const override;
    std::vector<PortInfo> inputPorts() const override;
};

//! Item representing sphere.

class SphereItem : public ParticleItem
{
public:
    static inline const std::string P_RADIUS = "Radius";

    SphereItem();
};

//! Item representing cylinder.

class CylinderItem : public ParticleItem
{
public:
    static inline const std::string P_RADIUS = "Radius";
    static inline const std::string P_HEIGHT = "Height";

    CylinderItem();
};

//! Represents transformation item box on the graphics scene.
//! Doesn't have input ports. Can be connected with particle items.

class TransformationItem : public ConnectableItem {
public:
    TransformationItem();

    std::vector<PortInfo> outputPorts() const override;
};

//! Lattice item.
//! Doesn't have input ports. Can be connected with layout items.

class LatticeItem : public ConnectableItem {
public:
    LatticeItem();

    std::vector<PortInfo> outputPorts() const override;
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_SAMPLEITEMS_H
