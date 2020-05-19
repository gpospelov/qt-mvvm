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

#include <functional>
#include <memory>
#include <vector>

namespace ModelView
{
class SessionModel;
}

class ModelHasChangedController;

//! Tracks changes in all models.
//! Allows to check if one or more models have been changed since last call of ::resetChanged().
//! This is intended to work together with the Project class. It will take care of calling
//! resetChanged after own saving.

//! To avoid extra signaling while being in already "changed" mode, the controller reports only
//! once.

class ProjectChangedController
{
public:
    using callback_t = std::function<void()>;
    ProjectChangedController(const std::vector<ModelView::SessionModel*>& models,
                             callback_t callback = {});
    ~ProjectChangedController();

    bool hasChanged() const;

    void resetChanged();

private:
    struct ProjectChangedControllerImpl;
    std::unique_ptr<ProjectChangedControllerImpl> p_impl;
};

#endif // PROJECTCHANGECONTROLLER_H
