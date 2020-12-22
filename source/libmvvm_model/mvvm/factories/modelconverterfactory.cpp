// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/factories/modelconverterfactory.h"
#include "mvvm/factories/itemconverterfactory.h"
#include "mvvm/serialization/jsonitem_types.h"
#include "mvvm/serialization/jsonmodelconverter.h"

//! Creates a JSON model converter intended for model cloning.
//! Saves a full deep copy of model in JSON. When restoring, reconstruct full copy.
//! This will lead to item ID's which are identical to original.

std::unique_ptr<ModelView::JsonModelConverterInterface> ModelView::CreateModelCloneConverter()
{
    return std::make_unique<JsonModelConverter>(ConverterMode::clone);
}

//! Creates a JSON model converter intended for model copying.
//! Saves a full deep copy of model in JSON. When restoring, reconstruct full copy and regenerate
//! item's ID to make them unique.

std::unique_ptr<ModelView::JsonModelConverterInterface> ModelView::CreateModelCopyConverter()
{
    return std::make_unique<JsonModelConverter>(ConverterMode::copy);
}

//! Creates a JSON model converter intended for save/load of the project on disk.
//! When saving to disk, only certain data is saved. When loading from disk, items
//! in memory is gently updated from JSON content.

std::unique_ptr<ModelView::JsonModelConverterInterface> ModelView::CreateModelProjectConverter()
{
    return std::make_unique<JsonModelConverter>(ConverterMode::project);
}
