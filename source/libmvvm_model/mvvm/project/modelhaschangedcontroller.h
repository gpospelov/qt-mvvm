// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_MODELHASCHANGEDCONTROLLER_H
#define MVVM_PROJECT_MODELHASCHANGEDCONTROLLER_H

#include "mvvm/signals/modellistener.h"
#include <functional>

namespace ModelView {

//! Tracks changes in the model.
//! Allows to check if model has been changed (e.g. modified, inserted or removed items) since last
//! call of ::resetChanged().

class MVVM_MODEL_EXPORT ModelHasChangedController : public ModelListener<SessionModel> {
public:
    using callback_t = std::function<void()>;
    ModelHasChangedController(SessionModel* model, callback_t callback = {});

    bool hasChanged() const;

    void resetChanged();

private:
    void process_change();
    bool m_has_changed{false};
    callback_t m_callback; //! informs the user about change in the model
};

} // namespace ModelView

#endif // MVVM_PROJECT_MODELHASCHANGEDCONTROLLER_H
