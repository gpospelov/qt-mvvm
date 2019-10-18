// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SampleViewFactory.h"
#include "InterferenceFunctionView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "ParticleLayoutView.h"
#include "item_constants.h"
#include <unordered_map>

namespace {
template <class T> IView* factory()
{
    return new T;
}
using FactoryFunc = IView*(*)();

const std::unordered_map<std::string, FactoryFunc> item_map{
    {Constants::MultiLayerType, factory<MultiLayerView>},
    {Constants::LayerType, factory<LayerView>},
    {Constants::ParticleLayoutType, factory<ParticleLayoutView>},
    {Constants::InterferenceFunctionType, factory<InterferenceFunctionView>}};
};

bool SampleViewFactory::isValidType(const std::string& name)
{
    return item_map.find(name) != item_map.end();
}

IView* SampleViewFactory::createSampleView(const std::string& name)
{
    return isValidType(name) ? item_map.at(name)() : nullptr;
}
