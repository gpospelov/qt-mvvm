// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEITEMS_H
#define SAMPLEITEMS_H

//! @file sampleitems.h
//! Classes to represent content of node editor.

#include "connectableitem.h"

namespace NodeEditor {

const std::string SphereItemType = "Sphere";
const std::string CylinderItemType = "Cylinder";
const std::string TransformationItemType = "Transformation";
const std::string ParticleLayoutItemType = "ParticleLayout";
const std::string LatticeItemType = "Lattice";

//! Represents particle item box on graph canvas.
//! It has two input ports: one to connect an arbitrary amount of particles of various shape,
//! another to connect a singel lattice.

class ParticleLayoutItem : public ConnectableItem {
public:
    static inline const std::string T_PARTICLE = "Particle";
    static inline const std::string T_LATTICE = "Lattice";
    ParticleLayoutItem();

    std::vector<PortInfo> inputPorts() const override;
};

//! Base class for particle presentation on the graphics canvas.
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
    SphereItem();
};

//! Item representing cylinder.

class CylinderItem : public ParticleItem
{
public:
    CylinderItem();
};

//! Represents transformation item box on graph canvas.

class TransformationItem : public ConnectableItem {
public:
    TransformationItem();

    std::vector<PortInfo> outputPorts() const override;
};

} // namespace NodeEditor

#endif
