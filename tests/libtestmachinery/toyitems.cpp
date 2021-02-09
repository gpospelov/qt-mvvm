// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "toyitems.h"
#include <QColor>
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/signals/itemmapper.h"
#include "mvvm/standarditems/vectoritem.h"
#include <stdexcept>

using namespace ToyItems;

MultiLayerItem::MultiLayerItem() : CompoundItem(Constants::MultiLayerItemType)
{
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS, {Constants::LayerItemType}),
                /*set_as_default*/ true);
}

LayerItem::LayerItem() : CompoundItem(Constants::LayerItemType)
{
    addProperty(P_THICKNESS, 42.0);
    addProperty(P_COLOR, QColor(Qt::green));
    registerTag(ModelView::TagInfo::universalTag(T_PARTICLES, {Constants::ParticleItemType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

ParticleItem::ParticleItem() : CompoundItem(Constants::ParticleItemType)
{
    addProperty<ModelView::VectorItem>(P_POSITION);
    addProperty<ShapeGroupItem>(P_SHAPES);
}

// ----------------------------------------------------------------------------

LatticeItem::LatticeItem() : CompoundItem(Constants::LatticeItemType)
{
    addProperty(P_ROTATION_ANLE, 90.0);
    addProperty(P_INTEGRATION, true);

    auto combo = ModelView::ComboProperty::createFrom({"Default", "Square", "Hexagonal"});
    addProperty(P_LATTICE_TYPE, combo);

    update_appearance();
}

void LatticeItem::activate()
{
    auto onIntegrationFlagChange = [this](SessionItem*, std::string property) {
        if (property == P_INTEGRATION)
            update_appearance();
    };
    mapper()->setOnPropertyChange(onIntegrationFlagChange, this);
}

void LatticeItem::update_appearance()
{
    auto angle_item = getItem(P_ROTATION_ANLE);
    angle_item->setEnabled(!property<bool>(P_INTEGRATION));
}

// ----------------------------------------------------------------------------

CylinderItem::CylinderItem() : CompoundItem(Constants::CylinderItemType)
{
    addProperty(P_RADIUS, 8.0);
    addProperty(P_HEIGHT, 10.0);
}

// ----------------------------------------------------------------------------

SphereItem::SphereItem() : CompoundItem(Constants::SphereItemType)
{
    addProperty(P_RADIUS, 8.0);
}

// ----------------------------------------------------------------------------

AnysoPyramidItem::AnysoPyramidItem() : CompoundItem(Constants::AnysoPyramidItemType)
{
    addProperty(P_LENGTH, 8.0);
    addProperty(P_WIDTH, 8.0);
    addProperty(P_HEIGHT, 8.0);
    addProperty(P_ALPHA, 8.0);
}

ShapeGroupItem::ShapeGroupItem() : GroupItem(Constants::ShapeGroupItemType)
{
    addToGroup<CylinderItem>("Cylinder");
    addToGroup<SphereItem>("Full sphere", /*make_selected*/ true);
    addToGroup<AnysoPyramidItem>("Anysotropical pyramid");
}
