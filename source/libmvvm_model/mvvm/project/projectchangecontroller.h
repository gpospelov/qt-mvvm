// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECTCHANGECONTROLLER_H
#define MVVM_PROJECT_PROJECTCHANGECONTROLLER_H

#include "mvvm/model_export.h"
#include <functional>
#include <memory>
#include <vector>

namespace ModelView {

class SessionModel;

//! Tracks changes in all models.
//! Allows to check if one or more models have been changed since last call of ::resetChanged().
//! This is intended to work together with the Project class. It will take care of calling
//! resetChanged after own saving.

//! To avoid extra signaling while being in already "changed" mode, the controller reports only
//! once.

class MVVM_MODEL_EXPORT ProjectChangedController {
public:
    using callback_t = std::function<void()>;
    ProjectChangedController(const std::vector<SessionModel*>& models,
                             callback_t project_changed_callback = {});
    ~ProjectChangedController();

    bool hasChanged() const;

    void resetChanged();

private:
    struct ProjectChangedControllerImpl;
    std::unique_ptr<ProjectChangedControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTCHANGECONTROLLER_H
