// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <modelinqmlcore/particlemodel.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/standarditems/vectoritem.h>

using namespace ModelView;

namespace
{

//! Constants to define toy items.
const std::string ParticleType = "Particle";
const std::string CylinderType = "Cylinder";
const std::string SphereType = "Sphere";
const std::string AnysoPyramidType = "AnysoPyramid";
const std::string ShapeGroupType = "ShapeGroup";

std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<ParticleItem>();
    result->registerItem<SphereItem>();
    result->registerItem<CylinderItem>();
    result->registerItem<AnysoPyramidItem>();
    result->registerItem<ShapeGroupItem>();
    return result;
}

} // namespace

ParticleItem::ParticleItem() : CompoundItem(ParticleType)
{
//    addProperty<VectorItem>(P_POSITION);
//    addProperty<ShapeGroupItem>(P_SHAPES);
    addProperty("Radius", 42.0);
    addProperty("Height", 10.0);
    addProperty("Alpha", 11.0);
}

CylinderItem::CylinderItem() : CompoundItem(CylinderType)
{
    addProperty(P_RADIUS, 8.0);
    addProperty(P_HEIGHT, 10.0);
}

SphereItem::SphereItem() : CompoundItem(SphereType)
{
    addProperty(P_RADIUS, 8.0);
}

AnysoPyramidItem::AnysoPyramidItem() : CompoundItem(AnysoPyramidType)
{
    addProperty(P_LENGTH, 8.0);
    addProperty(P_WIDTH, 9.0);
    addProperty(P_HEIGHT, 10.0);
    addProperty(P_ALPHA, 11.0);
}

ShapeGroupItem::ShapeGroupItem() : GroupItem(ShapeGroupType)
{
    registerItem<CylinderItem>("Cylinder");
    registerItem<SphereItem>("Full sphere", /*make_selected*/ true);
    registerItem<AnysoPyramidItem>("Anysotropical pyramid");
    init_group();
}

//! ---------------------------------------------------------------------------

ParticleModel::ParticleModel() : SessionModel("ParticleModel")
{
    setItemCatalogue(CreateItemCatalogue());
    insertItem<ParticleItem>();
}
