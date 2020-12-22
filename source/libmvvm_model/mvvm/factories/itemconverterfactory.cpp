// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/factories/itemconverterfactory.h"
#include "mvvm/serialization/jsonitem_types.h"
#include "mvvm/serialization/jsonitemconverter.h"

namespace ModelView {

//! Creates JSON item converter intended for item cloning.
//! Saves full deep copy of item to JSON. When restoring from JSON, reconstruct everything,
//! including item's unique ID. Used for backup.

std::unique_ptr<JsonItemConverterInterface>
CreateItemCloneConverter(const ItemFactoryInterface* item_factory)
{
    ConverterContext context{item_factory, ConverterMode::clone};
    return std::make_unique<JsonItemConverter>(context);
}

//! Creates JSON item converter intended for item copying.
//! Saves full deep copy of item to JSON. When restoring from JSON, will regenerate item's ID
//! to make it unique. Used for copying of item together with its children.

std::unique_ptr<JsonItemConverterInterface>
CreateItemCopyConverter(const ItemFactoryInterface* item_factory)
{
    ConverterContext context{item_factory, ConverterMode::copy};
    return std::make_unique<JsonItemConverter>(context);
}

//! Creates JSON item converter intended for saving on disk.
//! When saving on disk:
//! + Only selected data roles of items are saved (i.e. DATA, IDENTIFIER)
//! + All tags with its content are saved as usual
//! When loading from disk:
//! + Only selected roles are taken from JSON (i.e. DATA, IDENTIFIER), other roles (e.g. TOOLTIPS)
//!   are taken from memory.
//! + Property tags are updated, universal tags reconstructed.

std::unique_ptr<JsonItemConverterInterface>
CreateItemProjectConverter(const ItemFactoryInterface* item_factory)
{
    ConverterContext context{item_factory, ConverterMode::project};
    return std::make_unique<JsonItemConverter>(context);
}

} // namespace ModelView
