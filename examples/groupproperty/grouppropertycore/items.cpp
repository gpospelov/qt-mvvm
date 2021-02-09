// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "items.h"
#include "mvvm/standarditems/vectoritem.h"
#include <QColor>

namespace GroupProperty {

UndefinedShapeItem::UndefinedShapeItem() : ModelView::CompoundItem("Undefined")
{
    // no properties
}

SphereItem::SphereItem() : ModelView::CompoundItem("Sphere")
{
    addProperty("Radius", 5.0);
}

CylinderItem::CylinderItem() : ModelView::CompoundItem("Cylinder")
{
    addProperty("Radius", 8.0);
    addProperty("Height", 10.0);
}

BoxItem::BoxItem() : ModelView::CompoundItem("Box")
{
    addProperty("Length", 12.0);
    addProperty("Width", 6.0);
    addProperty("Height", 3.0);
}

ShapeGroupItem::ShapeGroupItem() : ModelView::GroupItem("Shape")
{
    addToGroup<UndefinedShapeItem>("xxx");
    addToGroup<SphereItem>("xxx");
    addToGroup<CylinderItem>("xxx");
    addToGroup<BoxItem>("xxx");
}

ParticleItem::ParticleItem() : ModelView::CompoundItem("Particle")
{
    addProperty("Color", QColor(Qt::green));
    addProperty<ModelView::VectorItem>("Position");
    addProperty<ShapeGroupItem>("Shape");
}

} // namespace GroupProperty
