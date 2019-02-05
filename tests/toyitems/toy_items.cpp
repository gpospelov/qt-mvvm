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
#include "toy_factories.h"
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

const std::string Vector::P_X = "X";
const std::string Vector::P_Y = "Y";
const std::string Vector::P_Z = "Z";

Vector::Vector() : CompoundItem(Constants::VectorType)
{
    addProperty<ModelView::PropertyItem>(P_X, 0.0);
    addProperty<ModelView::PropertyItem>(P_Y, 0.0);
    addProperty<ModelView::PropertyItem>(P_Z, 0.0);
}


// ----------------------------------------------------------------------------

const std::string Particle::P_POSITION = "Position";

Particle::Particle() : CompoundItem(Constants::ParticleType)
{
    addProperty<Vector>(P_POSITION);
}
