// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "toy_catalogue.h"
#include "toy_items.h"

std::unique_ptr<ModelView::ItemCatalogue> ToyItems::CreateToyItemCatalogue()
{
    auto result = ModelView::CreateDefaultItemCatalogue();
    result->add<MultiLayer>();
    result->add<Layer>();
    result->add<Particle>();
    result->add<InterferenceFunction>();
    result->add<Sphere>();
    result->add<Cylinder>();
    result->add<AnysoPyramid>();
    result->add<ShapeGroup>();
    return result;
}
