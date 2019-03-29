// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "toy_items.h"
#include "itemmanager.h"
#include "taginfo.h"
#include "toy_constants.h"
#include "vectoritem.h"
#include "itemmapper.h"
#include <stdexcept>

using namespace ToyItems;

const std::string MultiLayer::T_LAYERS = "layer tag";

MultiLayer::MultiLayer() : CompoundItem(Constants::MultiLayerType)
{
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS, {Constants::LayerType}),
                /*set_as_default*/ true);
}

const std::string Layer::P_THICKNESS = "Thickness";
const std::string Layer::T_PARTICLES = "Particles";

Layer::Layer() : CompoundItem(Constants::LayerType)
{
    addProperty<ModelView::PropertyItem>(P_THICKNESS, 42.0);
    registerTag(ModelView::TagInfo::universalTag(T_PARTICLES, {Constants::ParticleType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

const std::string Particle::P_POSITION = "Position";

Particle::Particle() : CompoundItem(Constants::ParticleType)
{
    addProperty<ModelView::VectorItem>(P_POSITION);
}

// ----------------------------------------------------------------------------

const std::string InterferenceFunction::P_ROTATION_ANLE = "Rotation";
const std::string InterferenceFunction::P_INTEGRATION = "Integration";

InterferenceFunction::InterferenceFunction()
    : CompoundItem(Constants::InterferenceType)
{
    addProperty<ModelView::PropertyItem>(P_ROTATION_ANLE, 90.0);
    addProperty<ModelView::PropertyItem>(P_INTEGRATION, true);

    update_appearance();
}

void InterferenceFunction::activate()
{
    mapper()->setOnPropertyChange([this](SessionItem*, std::string property) {
        if (property == P_INTEGRATION)
            update_appearance();
    }, this);
}

void InterferenceFunction::update_appearance()
{
    auto angle_item = getItem(P_ROTATION_ANLE);
    angle_item->setEnabled(!getItemValue(P_INTEGRATION).toBool());
}

std::unique_ptr<ModelView::ItemCatalogue> ToyItems::CreateToyItemCatalogue()
{
    auto result = ModelView::CreateDefaultItemCatalogue();
    result->add<MultiLayer>();
    result->add<Layer>();
    result->add<Particle>();
    result->add<InterferenceFunction>();
    return result;
}
