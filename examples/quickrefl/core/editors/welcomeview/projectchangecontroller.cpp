// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectchangecontroller.h"
#include "modelhaschangedcontroller.h"
#include <mvvm/model/sessionmodel.h>

using namespace ModelView;

ProjectChangedController::ProjectChangedController(const std::vector<SessionModel*>& models)
{
    for (auto model : models)
        change_controllers.emplace_back(std::make_unique<ModelHasChangedController>(model));
}

ProjectChangedController::~ProjectChangedController() = default;

bool ProjectChangedController::hasChanged() const
{
    for (const auto& controller : change_controllers)
        if (controller->hasChanged())
            return true;

    return false;
}

void ProjectChangedController::resetChanged()
{
    for (auto& controller : change_controllers)
        controller->resetChanged();
}
