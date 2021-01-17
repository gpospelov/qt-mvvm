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

const std::string ParticleItemType = "Particle";
const std::string TransformationItemType = "Transformation";

//! Represents particle item box on graph canvas.

class ParticleItem : public ConnectableItem {
public:
    static inline const std::string T_TRANSFORMATION = "Transformation";
    ParticleItem();

    std::vector<PortInfo> inputPorts() const override;
};

//! Represents transformation item box on graph canvas.

class TransformationItem : public ConnectableItem {
public:
    TransformationItem();

    std::vector<PortInfo> outputPorts() const override;
};

} // namespace NodeEditor

#endif
