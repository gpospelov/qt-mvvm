// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "toy_models.h"
#include "itemcatalogue.h"
#include "toy_items.h"

namespace  {
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue()
{
    std::unique_ptr<ModelView::ItemCatalogue> result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<ToyItems::MultiLayer>();
    result->registerItem<ToyItems::Layer>();
    result->registerItem<ToyItems::Particle>();
    result->registerItem<ToyItems::InterferenceFunction>();
    result->registerItem<ToyItems::Sphere>();
    result->registerItem<ToyItems::Cylinder>();
    result->registerItem<ToyItems::AnysoPyramid>();
    result->registerItem<ToyItems::ShapeGroup>();
    return result;
}
}


ToyItems::SampleModel::SampleModel() : SessionModel("ToyModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
}
