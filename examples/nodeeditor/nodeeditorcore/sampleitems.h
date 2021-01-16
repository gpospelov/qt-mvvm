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

#include "mvvm/model/compounditem.h"
#include "portinfo.h"

class QColor;

namespace NodeEditor {

const std::string ParticleItemType = "Particle";
const std::string TransformationItemType = "Transformation";

//! Base class for all node editor items.

class ConnectableItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_XPOS = "P_XPOS";
    static inline const std::string P_YPOS = "P_YPOS";
    static inline const std::string P_COLOR = "P_COLOR";

    explicit ConnectableItem(const std::string& modelType);

    QColor color() const;

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    void setNamedColor(const std::string& named_color);

    virtual std::vector<PortInfo> inputPorts() const;

    virtual std::vector<PortInfo> outputPorts() const;
};

//! Represents particle item box on graph canvas.

class ParticleItem : public ConnectableItem {
public:
    static inline const std::string T_TRANSFORMATION = "Transformation";
    ParticleItem();
};

//! Represents transformation item box on graph canvas.

class TransformationItem : public ConnectableItem {
public:
    TransformationItem();
};

} // namespace NodeEditor

#endif
