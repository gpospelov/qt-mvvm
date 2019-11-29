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

#include <mvvm/model/compounditem.h>
#include <mvvm/model/groupitem.h>
#include <string>

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

namespace Constants
{

const ModelView::model_type MultiLayerType = "MultiLayer";
const ModelView::model_type LayerType = "Layer";
const ModelView::model_type ParticleType = "Particle";
const ModelView::model_type InterferenceType = "Interference";

const ModelView::model_type CylinderType = "Cylinder";
const ModelView::model_type SphereType = "Sphere";
const ModelView::model_type AnysoPyramidType = "AnysoPyramid";

const ModelView::model_type ShapeGroupType = "ShapeGroup";
} // namespace Constants

// ----------------------------------------------------------------------------

class MultiLayerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string T_LAYERS = "T_LAYERS";
    MultiLayerItem();
};

// ----------------------------------------------------------------------------

class LayerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_THICKNESS = "Thickness";
    static inline const std::string P_COLOR = "Color";
    static inline const std::string T_PARTICLES = "Particles";
    LayerItem();
};

// ----------------------------------------------------------------------------

class ParticleItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_POSITION = "Position";
    static inline const std::string P_SHAPES = "Shapes";

    ParticleItem();
};

// ----------------------------------------------------------------------------

class InterferenceFunctionItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_ROTATION_ANLE = "Rotation";
    static inline const std::string P_INTEGRATION = "Integration";
    static inline const std::string P_LATTICE_TYPE = "Lattice type";

    InterferenceFunctionItem();

    void activate() override;

private:
    void update_appearance();
};

// ----------------------------------------------------------------------------

class CylinderItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_RADIUS = "Radius";
    static inline const std::string P_HEIGHT = "Height";

    CylinderItem();
};

class SphereItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_RADIUS = "Radius";

    SphereItem();
};

class AnysoPyramidItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_LENGTH = "Length";
    static inline const std::string P_WIDTH = "Width";
    static inline const std::string P_HEIGHT = "Height";
    static inline const std::string P_ALPHA = "Alpha";

    AnysoPyramidItem();
};

class ShapeGroupItem : public ModelView::GroupItem
{
public:
    ShapeGroupItem();
};

} // namespace ToyItems

#endif // TOYITEMS_H
