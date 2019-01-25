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

Layer::Layer() : CompoundItem(Constants::LayerType)
{
//    addProperty(P_THICKNESS, 42.0);
}
