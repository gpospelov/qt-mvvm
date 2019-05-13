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
    result->add<ToyItems::MultiLayer>();
    result->add<ToyItems::Layer>();
    result->add<ToyItems::Particle>();
    result->add<ToyItems::InterferenceFunction>();
    result->add<ToyItems::Sphere>();
    result->add<ToyItems::Cylinder>();
    result->add<ToyItems::AnysoPyramid>();
    result->add<ToyItems::ShapeGroup>();
    return result;
}
}


ToyItems::SampleModel::SampleModel() : SessionModel("ToyModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
}
