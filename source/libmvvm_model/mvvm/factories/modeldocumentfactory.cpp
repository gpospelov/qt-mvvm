// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/factories/modeldocumentfactory.h"
#include "mvvm/serialization/jsondocument.h"

namespace ModelView {

std::unique_ptr<ModelDocumentInterface> CreateJsonDocument(const std::vector<SessionModel*>& models)
{
    return std::make_unique<JsonDocument>(models);
}

} // namespace ModelView
