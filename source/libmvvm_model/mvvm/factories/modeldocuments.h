// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_MODELDOCUMENTS_H
#define MVVM_FACTORIES_MODELDOCUMENTS_H

#include <initializer_list>
#include <memory>
#include <mvvm/interfaces/modeldocumentinterface.h>

namespace ModelView
{

class SessionModel;

//! Creates JsonDocument to save and load models.
MVVM_MODEL_EXPORT std::unique_ptr<ModelDocumentInterface>
CreateJsonDocument(std::initializer_list<SessionModel*> models);

} // namespace ModelView

#endif // MVVM_FACTORIES_MODELDOCUMENTS_H
