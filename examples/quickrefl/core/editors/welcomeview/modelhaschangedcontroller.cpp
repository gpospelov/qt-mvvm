// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modelhaschangedcontroller.h"

using namespace ModelView;

ModelHasChangedController::ModelHasChangedController(ModelView::SessionModel* model,
                                                     callback_t callback)
    : ModelListener(model), m_callback(callback)
{
    setOnDataChange([this](auto, auto) { process_change(); });
    setOnItemInserted([this](auto, auto) { process_change(); });
    setOnItemRemoved([this](auto, auto) { process_change(); });
    setOnModelReset([this](auto) { process_change(); });
}

//! Returns true if the model was changed in any way since last call of resetChanged.

bool ModelHasChangedController::hasChanged() const
{
    return has_changed;
}

//! Reset has_changed flag.

void ModelHasChangedController::resetChanged()
{
    has_changed = false;
}

void ModelHasChangedController::process_change()
{
    has_changed = true;
    if (m_callback)
        m_callback();
}
