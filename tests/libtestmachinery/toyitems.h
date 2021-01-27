// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TOYITEMS_H
#define TOYITEMS_H

#include "mvvm/model/compounditem.h"
#include "mvvm/model/groupitem.h"
#include <string>

//! Collection of toy items and models for testing purposes.

namespace ToyItems {

namespace Constants {

const ModelView::model_type MultiLayerItemType = "MultiLayer";
const ModelView::model_type LayerItemType = "Layer";
const ModelView::model_type ParticleItemType = "Particle";
const ModelView::model_type LatticeItemType = "Lattice";

const ModelView::model_type CylinderItemType = "Cylinder";
const ModelView::model_type SphereItemType = "Sphere";
const ModelView::model_type AnysoPyramidItemType = "AnysoPyramid";

const ModelView::model_type ShapeGroupItemType = "ShapeGroup";
} // namespace Constants

//! Represents multilayer with collection of layers.

class MultiLayerItem : public ModelView::CompoundItem {
public:
    static inline const std::string T_LAYERS = "T_LAYERS";
    MultiLayerItem();
};

//! Represents a layer, with thickness and color, and possibly populated with particles.

class LayerItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_THICKNESS = "Thickness";
    static inline const std::string P_COLOR = "Color";
    static inline const std::string T_PARTICLES = "Particles";
    LayerItem();
};

//! Represents a particle, with a position, and a selection of possible shapes.

class ParticleItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_POSITION = "Position";
    static inline const std::string P_SHAPES = "Shapes";

    ParticleItem();
};

//! Represents a lattice.

class LatticeItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_ROTATION_ANLE = "Rotation";
    static inline const std::string P_INTEGRATION = "Integration";
    static inline const std::string P_LATTICE_TYPE = "Lattice type";

    LatticeItem();

    void activate() override;

private:
    void update_appearance();
};

//! Represents a cylindrical shape.

class CylinderItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_RADIUS = "Radius";
    static inline const std::string P_HEIGHT = "Height";

    CylinderItem();
};

//! Represents a shpere.

class SphereItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_RADIUS = "Radius";

    SphereItem();
};

//! Represents an anysotropical pyramid.

class AnysoPyramidItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_LENGTH = "Length";
    static inline const std::string P_WIDTH = "Width";
    static inline const std::string P_HEIGHT = "Height";
    static inline const std::string P_ALPHA = "Alpha";

    AnysoPyramidItem();
};

//! Represents a group item holding a collection of shapes.

class ShapeGroupItem : public ModelView::GroupItem {
public:
    ShapeGroupItem();
};

} // namespace ToyItems

#endif // TOYITEMS_H
