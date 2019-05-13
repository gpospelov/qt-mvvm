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
#include "comboproperty.h"
#include "itemmanager.h"
#include "itemmapper.h"
#include "taginfo.h"
#include "vectoritem.h"
#include <QColor>
#include <stdexcept>


const std::string MultiLayer::T_LAYERS = "layer tag";

MultiLayer::MultiLayer() : CompoundItem(Constants::MultiLayerType)
{
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS, {Constants::LayerType}),
                /*set_as_default*/ true);
}

const std::string Layer::P_THICKNESS = "Thickness";
const std::string Layer::P_COLOR = "Color";
const std::string Layer::T_PARTICLES = "Particles";

Layer::Layer() : CompoundItem(Constants::LayerType)
{
    addProperty<ModelView::PropertyItem>(P_THICKNESS, 42.0);
    addProperty<ModelView::PropertyItem>(P_COLOR, QColor(Qt::green));
    registerTag(ModelView::TagInfo::universalTag(T_PARTICLES, {Constants::ParticleType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

const std::string Particle::P_POSITION = "Position";
const std::string Particle::P_SHAPES = "Shapes";

Particle::Particle() : CompoundItem(Constants::ParticleType)
{
    addProperty<ModelView::VectorItem>(P_POSITION);
    addProperty<ShapeGroup>(P_SHAPES);
}

// ----------------------------------------------------------------------------

const std::string InterferenceFunction::P_ROTATION_ANLE = "Rotation";
const std::string InterferenceFunction::P_INTEGRATION = "Integration";
const std::string InterferenceFunction::P_LATTICE_TYPE = "Lattice";

InterferenceFunction::InterferenceFunction() : CompoundItem(Constants::InterferenceType)
{
    addProperty<ModelView::PropertyItem>(P_ROTATION_ANLE, 90.0);
    addProperty<ModelView::PropertyItem>(P_INTEGRATION, true);

    ModelView::ComboProperty combo =
        ModelView::ComboProperty::createFrom({"Default", "Square", "Hexagonal"});
    addProperty<ModelView::PropertyItem>(P_LATTICE_TYPE, combo.variant());

    update_appearance();
}

void InterferenceFunction::activate()
{
    auto onIntegrationFlagChange = [this](SessionItem*, std::string property) {
        if (property == P_INTEGRATION)
            update_appearance();
    };

    mapper()->setOnPropertyChange(onIntegrationFlagChange, this);
}

void InterferenceFunction::update_appearance()
{
    auto angle_item = getItem(P_ROTATION_ANLE);
    angle_item->setEnabled(!getItemValue(P_INTEGRATION).toBool());
}

// ----------------------------------------------------------------------------

const std::string Cylinder::P_RADIUS = "Radius";
const std::string Cylinder::P_HEIGHT = "Height";

Cylinder::Cylinder() : CompoundItem(Constants::CylinderType)
{
    addProperty<ModelView::PropertyItem>(P_RADIUS, 8.0);
    addProperty<ModelView::PropertyItem>(P_HEIGHT, 10.0);
}

// ----------------------------------------------------------------------------

const std::string Sphere::P_RADIUS = "Radius";

Sphere::Sphere() : CompoundItem(Constants::SphereType)
{
    addProperty<ModelView::PropertyItem>(P_RADIUS, 8.0);
}

// ----------------------------------------------------------------------------

const std::string AnysoPyramid::P_LENGTH = "Length";
const std::string AnysoPyramid::P_WIDTH = "Width";
const std::string AnysoPyramid::P_HEIGHT = "Height";
const std::string AnysoPyramid::P_ALPHA = "Alpha";

AnysoPyramid::AnysoPyramid() : CompoundItem(Constants::AnysoPyramidType)
{
    addProperty<ModelView::PropertyItem>(P_LENGTH, 8.0);
    addProperty<ModelView::PropertyItem>(P_WIDTH, 8.0);
    addProperty<ModelView::PropertyItem>(P_HEIGHT, 8.0);
    addProperty<ModelView::PropertyItem>(P_ALPHA, 8.0);
}

ShapeGroup::ShapeGroup() : GroupItem(Constants::ShapeGroupType)
{
    registerItem<Cylinder>("Cylinder");
    registerItem<Sphere>("Full sphere", /*make_selected*/true);
    registerItem<AnysoPyramid>("Anysotropical pyramid");
    init_group();
}
