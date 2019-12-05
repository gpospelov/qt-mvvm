// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/core/modeldocuments.h>
#include <mvvm/serialization/jsondocument.h>

namespace ModelView
{

std::unique_ptr<ModelDocumentInterface>
CreateJsonDocument(std::initializer_list<SessionModel*> models)
{
    return std::make_unique<JsonDocument>(models);
}

} // namespace ModelView
