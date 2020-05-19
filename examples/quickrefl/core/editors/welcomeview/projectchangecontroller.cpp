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

struct ProjectChangedController::ProjectChangedControllerImpl {
    std::vector<SessionModel*> m_models;
    std::vector<std::unique_ptr<ModelHasChangedController>> change_controllers;

    ProjectChangedControllerImpl(const std::vector<SessionModel*>& models) : m_models(models)
    {
        create_controllers();
    }

    void create_controllers()
    {
        change_controllers.clear();
        for (auto model : m_models)
            change_controllers.emplace_back(std::make_unique<ModelHasChangedController>(model));
    }

    bool hasChanged() const
    {
        for (const auto& controller : change_controllers)
            if (controller->hasChanged())
                return true;

        return false;
    }

    void resetChanged()
    {
        for (auto& controller : change_controllers)
            controller->resetChanged();
    }
};

ProjectChangedController::ProjectChangedController(const std::vector<SessionModel*>& models)
    : p_impl(std::make_unique<ProjectChangedControllerImpl>(models))
{
}

ProjectChangedController::~ProjectChangedController() = default;

//! Returns true if the change in the models has been registered since the last call of resetChanged.

bool ProjectChangedController::hasChanged() const
{
    return p_impl->hasChanged();
}

//! Reset controller to initial state, pretending that no changes has been registered.

void ProjectChangedController::resetChanged()
{
    return p_impl->resetChanged();
}
