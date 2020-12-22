// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/project/modelhaschangedcontroller.h"

using namespace ModelView;

//! Constructor of ModelHasChangedController.
//! Acccept 'model' to listen, and a 'callback' to report about changes in a model.

ModelHasChangedController::ModelHasChangedController(SessionModel* model, callback_t callback)
    : ModelListener(model), m_callback(callback)
{
    setOnDataChange([this](auto, auto) { process_change(); });
    setOnItemInserted([this](auto, auto) { process_change(); });
    setOnItemRemoved([this](auto, auto) { process_change(); });
    setOnModelReset([this](auto) { process_change(); });
}

//! Returns true if the model was changed since last call of resetChanged.

bool ModelHasChangedController::hasChanged() const
{
    return m_has_changed;
}

//! Reset has_changed flag.

void ModelHasChangedController::resetChanged()
{
    m_has_changed = false;
}

//! Sets 'has_changed' flag and reports back to client.

void ModelHasChangedController::process_change()
{
    m_has_changed = true;
    if (m_callback)
        m_callback();
}
