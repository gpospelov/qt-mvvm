// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_PROGRESSHANDLER_H
#define MVVM_UTILS_PROGRESSHANDLER_H

#include "mvvm/model_export.h"
#include <functional>
#include <mutex>

namespace ModelView {

//! Maintain information about progress of a computation.
//! Initialized with callback function to report progress and retrieve interruption request status.

class MVVM_MODEL_EXPORT ProgressHandler {
public:
    using callback_t = std::function<bool(size_t)>;

    ProgressHandler() = default;
    ProgressHandler(callback_t callback, size_t max_ticks_count);

    ProgressHandler(const ProgressHandler& other) = delete;
    ProgressHandler& operator=(const ProgressHandler& other) = delete;

    void subscribe(callback_t callback);

    void setMaxTicksCount(size_t value);

    bool has_interrupt_request() const;

    void setCompletedTicks(size_t value);

    void reset();

private:
    std::mutex mutex;
    callback_t runner_callback;
    size_t max_ticks_count{0};
    size_t completed_ticks{0};
    bool interrupt_request{false};
};

} // namespace ModelView

#endif // MVVM_UTILS_PROGRESSHANDLER_H
