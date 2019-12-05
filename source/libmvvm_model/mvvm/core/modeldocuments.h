// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_CORE_MODELDOCUMENTS_H
#define MVVM_CORE_MODELDOCUMENTS_H

#include <initializer_list>
#include <memory>
#include <mvvm/core/export.h>
#include <mvvm/core/modeldocumentinterface.h>

namespace ModelView
{

class SessionModel;

//! Creates JsonDocument to save and load models.
CORE_EXPORT std::unique_ptr<ModelDocumentInterface>
CreateJsonDocument(std::initializer_list<SessionModel*> models);

} // namespace ModelView

#endif // MVVM_CORE_MODELDOCUMENTINTERFACE_H
