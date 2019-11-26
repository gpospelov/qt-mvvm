// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef FLATEDITORCORE_ITEMS_H
#define FLATEDITORCORE_ITEMS_H

//! @file items.h
//! Collection of test items for our sample model.

#include <mvvm/model/compounditem.h>
#include <mvvm/model/groupitem.h>
#include <string>

/*!
@class MultiLayer
@brief A multi layer with possibility to attach layers.
*/

class MultiLayer : public ModelView::CompoundItem
{
public:
    static inline const std::string T_LAYERS = "T_LAYERS";
    MultiLayer();
};

/*!
@class LayerItem
@brief A layer with thickness, color property and possibility to attach particles.
*/

class LayerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_THICKNESS = "Thickness";
    static inline const std::string P_COLOR = "Color";
    static inline const std::string T_PARTICLES = "Particles";
    LayerItem();
};

/*!
@class ParticleItem
@brief A particle with position and shape group.

Demonstrates how to create group of properties.
*/

class ParticleItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_POSITION = "Position";
    static inline const std::string P_SHAPES = "Shapes";
    ParticleItem();
};

/*!
@class InterferenceFunctionItem
@brief Interference function with bool, double and combo on board.

Demonstrates how to syncronize properties between each other.
*/

class InterferenceFunctionItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_ROTATION_ANLE = "Rotation";
    static inline const std::string P_INTEGRATION = "Integration";
    static inline const std::string P_LATTICE_TYPE = "Lattice";

    InterferenceFunctionItem();

    void activate() override;

private:
    void update_appearance();
};

/*!
@class CylinderItem
@brief Simple cylinder with radius and height.
*/

class CylinderItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_RADIUS = "Radius";
    static inline const std::string P_HEIGHT = "Height";
    CylinderItem();
};

/*!
@class SphereItem
@brief Simple spherer with radius.
*/

class SphereItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_RADIUS = "Radius";
    SphereItem();
};

/*!
@class AnysoPyramidItem
@brief Pyramid with 4 parameters.
*/

class AnysoPyramidItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_LENGTH = "Length";
    static inline const std::string P_WIDTH = "Width";
    static inline const std::string P_HEIGHT = "Height";
    static inline const std::string P_ALPHA = "Alpha";
    AnysoPyramidItem();
};

/*!
@class AnysoPyramidItem
@brief Special group of shapes.
*/

class ShapeGroupItem : public ModelView::GroupItem
{
public:
    ShapeGroupItem();
};

#endif // FLATEDITORCORE_ITEMS_H
