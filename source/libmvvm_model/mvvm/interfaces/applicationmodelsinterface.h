// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_APPLICATIONMODELSINTERFACE_H
#define MVVM_INTERFACES_APPLICATIONMODELSINTERFACE_H

#include "mvvm/model_export.h"
#include <vector>

namespace ModelView {

class SessionModel;

//! Interface to access application's model list for further manipulation.
//! Used in the context of save/load projects.

class MVVM_MODEL_EXPORT ApplicationModelsInterface {
public:
    //! Returns vector of models intended for saving on disk.
    virtual std::vector<SessionModel*> persistent_models() const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_APPLICATIONMODELSINTERFACE_H
