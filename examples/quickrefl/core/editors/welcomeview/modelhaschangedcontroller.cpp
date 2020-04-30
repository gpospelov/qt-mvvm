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

ModelHasChangedController::ModelHasChangedController(ModelView::SessionModel* model)
    : ModelListener(model)
{
    setOnDataChange([this](auto, auto) { has_changed = true; });
    setOnItemInserted([this](auto, auto) { has_changed = true; });
    setOnItemRemoved([this](auto, auto) { has_changed = true; });
    setOnModelReset([this](auto) { has_changed = true; });
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
