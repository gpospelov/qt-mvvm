// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef ITEMS_H
#define ITEMS_H

//! @file items.h
//! Collection of test items for our sample model.

#include "compounditem.h"
#include "groupitem.h"
#include <string>

/*!
@class MultiLayer
@brief A multi layer with possibility to attach layers.
*/

class MultiLayer : public ModelView::CompoundItem
{
public:
    static const std::string T_LAYERS;
    MultiLayer();
};

/*!
@class LayerItem
@brief A layer with thickness, color property and possibility to attach particles.
*/

class LayerItem : public ModelView::CompoundItem
{
public:
    static const std::string P_THICKNESS;
    static const std::string P_COLOR;
    static const std::string T_PARTICLES;
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
    static const std::string P_POSITION;
    static const std::string P_SHAPES;
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
    static const std::string P_ROTATION_ANLE;
    static const std::string P_INTEGRATION;
    static const std::string P_LATTICE_TYPE;

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
    static const std::string P_RADIUS;
    static const std::string P_HEIGHT;
    CylinderItem();
};

/*!
@class SphereItem
@brief Simple spherer with radius.
*/

class SphereItem : public ModelView::CompoundItem
{
public:
    static const std::string P_RADIUS;
    SphereItem();
};

/*!
@class AnysoPyramidItem
@brief Pyramid with 4 parameters.
*/

class AnysoPyramidItem : public ModelView::CompoundItem
{
public:
    static const std::string P_LENGTH;
    static const std::string P_WIDTH;
    static const std::string P_HEIGHT;
    static const std::string P_ALPHA;
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

#endif // ITEMS_H
