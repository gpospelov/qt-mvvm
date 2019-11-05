// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "items.h"
#include "item_constants.h"
#include <mvvm/model/comboproperty.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/standarditems/vectoritem.h>
#include <QColor>

using namespace ModelView;

MultiLayer::MultiLayer() : CompoundItem(::Constants::MultiLayerType)
{
    registerTag(TagInfo::universalTag(T_LAYERS, {::Constants::LayerType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

LayerItem::LayerItem() : CompoundItem(::Constants::LayerType)
{
    addProperty(P_THICKNESS, 42.0);
    addProperty(P_COLOR, QColor(Qt::green));
    registerTag(TagInfo::universalTag(T_PARTICLES, {::Constants::ParticleType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

ParticleItem::ParticleItem() : CompoundItem(::Constants::ParticleType)
{
    addProperty<VectorItem>(P_POSITION);
    addProperty<ShapeGroupItem>(P_SHAPES);
}

// ----------------------------------------------------------------------------

InterferenceFunctionItem::InterferenceFunctionItem() : CompoundItem(::Constants::InterferenceType)
{
    addProperty(P_ROTATION_ANLE, 90.0);
    addProperty(P_INTEGRATION, true);

    auto combo = ComboProperty::createFrom({"Default", "Square", "Hexagonal"});
    addProperty(P_LATTICE_TYPE, combo);

    update_appearance();
}

void InterferenceFunctionItem::activate()
{
    auto onIntegrationFlagChange = [this](SessionItem*, std::string property) {
        if (property == P_INTEGRATION)
            update_appearance();
    };

    mapper()->setOnPropertyChange(onIntegrationFlagChange, this);
}

void InterferenceFunctionItem::update_appearance()
{
    auto angle_item = getItem(P_ROTATION_ANLE);
    angle_item->setEnabled(!property(P_INTEGRATION).value<bool>());
}

// ----------------------------------------------------------------------------

CylinderItem::CylinderItem() : CompoundItem(::Constants::CylinderType)
{
    addProperty(P_RADIUS, 8.0);
    addProperty(P_HEIGHT, 10.0);
}

// ----------------------------------------------------------------------------

SphereItem::SphereItem() : CompoundItem(::Constants::SphereType)
{
    addProperty(P_RADIUS, 8.0);
}

// ----------------------------------------------------------------------------

AnysoPyramidItem::AnysoPyramidItem() : CompoundItem(::Constants::AnysoPyramidType)
{
    addProperty(P_LENGTH, 8.0);
    addProperty(P_WIDTH, 9.0);
    addProperty(P_HEIGHT, 10.0);
    addProperty(P_ALPHA, 11.0);
}

// ----------------------------------------------------------------------------

ShapeGroupItem::ShapeGroupItem() : GroupItem(::Constants::ShapeGroupType)
{
    registerItem<CylinderItem>("Cylinder");
    registerItem<SphereItem>("Full sphere", /*make_selected*/true);
    registerItem<AnysoPyramidItem>("Anysotropical pyramid");
    init_group();
}
