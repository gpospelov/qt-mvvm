// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/factories/itemconverterfactory.h>
#include <mvvm/factories/modelconverterfactory.h>
#include <mvvm/serialization/jsonmodelconverter.h>

std::unique_ptr<ModelView::JsonModelConverterInterface> ModelView::CreateModelCopyConverter()
{
    // FIXME
    return std::make_unique<JsonModelConverter>();
}

std::unique_ptr<ModelView::JsonModelConverterInterface> ModelView::CreateModelProjectConverter()
{
    return std::make_unique<JsonModelConverter>();
}
