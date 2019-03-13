// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "defaultitemcatalogue.h"
#include "model_types.h"
#include "vectoritem.h"
#include "propertyitem.h"
#include "compounditem.h"

//using namespace ModelView;

ModelView::ItemCatalogue ModelView::CreateDefaultItemCatalogue()
{
    ModelView::ItemCatalogue result;
    result.add<ModelView::PropertyItem>();
    result.add<ModelView::CompoundItem>();
    result.add<ModelView::VectorItem>();
    return result;
}
