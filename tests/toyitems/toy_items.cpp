// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "toy_items.h"
#include <mvvm/model/comboproperty.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/model/taginfo.h>
#include "toy_constants.h"
#include <mvvm/standarditems/vectoritem.h>
#include <QColor>
#include <stdexcept>

using namespace ToyItems;

const std::string MultiLayerItem::T_LAYERS = "layer tag";

MultiLayerItem::MultiLayerItem() : CompoundItem(Constants::MultiLayerType)
{
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS, {Constants::LayerType}),
                /*set_as_default*/ true);
}

const std::string LayerItem::P_THICKNESS = "Thickness";
const std::string LayerItem::P_COLOR = "Color";
const std::string LayerItem::T_PARTICLES = "Particles";

LayerItem::LayerItem() : CompoundItem(Constants::LayerType)
{
    addProperty(P_THICKNESS, 42.0);
    addProperty(P_COLOR, QColor(Qt::green));
    registerTag(ModelView::TagInfo::universalTag(T_PARTICLES, {Constants::ParticleType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

const std::string ParticleItem::P_POSITION = "Position";
const std::string ParticleItem::P_SHAPES = "Shapes";

ParticleItem::ParticleItem() : CompoundItem(Constants::ParticleType)
{
    addProperty<ModelView::VectorItem>(P_POSITION);
    addProperty<ShapeGroupItem>(P_SHAPES);
}

// ----------------------------------------------------------------------------

const std::string InterferenceFunctionItem::P_ROTATION_ANLE = "Rotation";
const std::string InterferenceFunctionItem::P_INTEGRATION = "Integration";
const std::string InterferenceFunctionItem::P_LATTICE_TYPE = "Lattice";

InterferenceFunctionItem::InterferenceFunctionItem() : CompoundItem(Constants::InterferenceType)
{
    addProperty(P_ROTATION_ANLE, 90.0);
    addProperty(P_INTEGRATION, true);

    auto combo = ModelView::ComboProperty::createFrom({"Default", "Square", "Hexagonal"});
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

const std::string CylinderItem::P_RADIUS = "Radius";
const std::string CylinderItem::P_HEIGHT = "Height";

CylinderItem::CylinderItem() : CompoundItem(Constants::CylinderType)
{
    addProperty(P_RADIUS, 8.0);
    addProperty(P_HEIGHT, 10.0);
}

// ----------------------------------------------------------------------------

const std::string SphereItem::P_RADIUS = "Radius";

SphereItem::SphereItem() : CompoundItem(Constants::SphereType)
{
    addProperty(P_RADIUS, 8.0);
}

// ----------------------------------------------------------------------------

const std::string AnysoPyramidItem::P_LENGTH = "Length";
const std::string AnysoPyramidItem::P_WIDTH = "Width";
const std::string AnysoPyramidItem::P_HEIGHT = "Height";
const std::string AnysoPyramidItem::P_ALPHA = "Alpha";

AnysoPyramidItem::AnysoPyramidItem() : CompoundItem(Constants::AnysoPyramidType)
{
    addProperty(P_LENGTH, 8.0);
    addProperty(P_WIDTH, 8.0);
    addProperty(P_HEIGHT, 8.0);
    addProperty(P_ALPHA, 8.0);
}

ShapeGroupItem::ShapeGroupItem() : GroupItem(Constants::ShapeGroupType)
{
    registerItem<CylinderItem>("Cylinder");
    registerItem<SphereItem>("Full sphere", /*make_selected*/true);
    registerItem<AnysoPyramidItem>("Anysotropical pyramid");
    init_group();
}
