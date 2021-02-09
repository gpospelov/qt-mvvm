// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GROUPPROPERTYCORE_ITEMS_H
#define GROUPPROPERTYCORE_ITEMS_H

#include "mvvm/model/compounditem.h"
#include "mvvm/model/groupitem.h"

namespace GroupProperty {

//! Represents undefined shape.

class UndefinedShapeItem : public ModelView::CompoundItem {
public:
    UndefinedShapeItem();
};

//! Represents a shpere.

class SphereItem : public ModelView::CompoundItem {
public:
    SphereItem();
};

//! Represents a cylindrical shape.

class CylinderItem : public ModelView::CompoundItem {
public:
    CylinderItem();
};

//! Represents a box.

class BoxItem : public ModelView::CompoundItem {
public:
    BoxItem();
};

//! Represents a group of possible shapes.

class ShapeGroupItem : public ModelView::GroupItem {
public:
    ShapeGroupItem();
};

//! Represents a particle. Particle has a color, position, and a selection of possible shapes.

class ParticleItem : public ModelView::CompoundItem {
public:
    ParticleItem();
};

} // namespace GroupProperty

#endif // GROUPPROPERTYCORE_ITEMS_H
