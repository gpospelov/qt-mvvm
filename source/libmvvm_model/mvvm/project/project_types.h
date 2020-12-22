// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECT_TYPES_H
#define MVVM_PROJECT_PROJECT_TYPES_H

#include "mvvm/model_export.h"
#include <functional>
#include <string>
#include <vector>

namespace ModelView {

class SessionModel;

//! Possible user answers on question "Project was modified".
enum class SaveChangesAnswer { SAVE = 0, DISCARD = 1, CANCEL = 2 };

//! Provides necessary information for Project construction.

struct MVVM_MODEL_EXPORT ProjectContext {
    //!< To notify about the change of the project with respect to what was written on disk.
    using modified_callback_t = std::function<void()>;

    //! To ask for a vector of models to save/load to/from disk.
    //! This is intentionally obtained via callback since save request might come after
    //! the Project construction.
    using models_callback_t = std::function<std::vector<SessionModel*>()>;

    modified_callback_t m_modified_callback;
    models_callback_t m_models_callback;
};

//! Defines the context to interact with the user regarding save/save-as/create-new project
//! scenarious.

struct MVVM_MODEL_EXPORT UserInteractionContext {
    //!< To ask the user to select existing directory, returns full path to the directory.
    using select_dir_callback_t = std::function<std::string()>;

    //!< To ask the user to create a new directory, returns full path to the directory.
    using create_dir_callback_t = std::function<std::string()>;

    //!< To ask the user what to do with modified project.
    using answer_callback_t = std::function<SaveChangesAnswer()>;

    select_dir_callback_t m_select_dir_callback;
    create_dir_callback_t m_create_dir_callback;
    answer_callback_t m_answer_callback;
};

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECT_TYPES_H
