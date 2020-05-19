// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTCHANGECONTROLLER_H
#define PROJECTCHANGECONTROLLER_H

#include <memory>
#include <vector>

namespace ModelView
{
class SessionModel;
}

class ModelHasChangedController;

//! Tracks changes in all models.
//! Allows to check if one or more models have been changed since last call of ::resetChanged().

class ProjectChangedController
{
public:
    ProjectChangedController(const std::vector<ModelView::SessionModel*>& models);
    ~ProjectChangedController();

    bool hasChanged() const;

    void resetChanged();

private:
    struct ProjectChangedControllerImpl;
    std::unique_ptr<ProjectChangedControllerImpl> p_impl;
};

#endif // PROJECTCHANGECONTROLLER_H
