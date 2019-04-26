// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "defaultitemcatalogue.h"
#include "mvvm_types.h"
#include "vectoritem.h"
#include "propertyitem.h"
#include "compounditem.h"

//using namespace ModelView;

std::unique_ptr<ModelView::ItemCatalogue> ModelView::CreateDefaultItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->add<ModelView::SessionItem>();
    result->add<ModelView::PropertyItem>();
    result->add<ModelView::CompoundItem>();
    result->add<ModelView::VectorItem>();
    return result;
}
