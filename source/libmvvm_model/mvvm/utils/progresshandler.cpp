// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/utils/progresshandler.h"
#include <cstddef>
#include <mutex>
#include <utility>

using namespace ModelView;

ProgressHandler::ProgressHandler(ProgressHandler::callback_t callback, size_t max_ticks_count)
    : m_runner_callback(std::move(callback)), m_max_ticks_count(max_ticks_count)
{
}

void ProgressHandler::subscribe(ProgressHandler::callback_t callback)
{
    m_runner_callback = std::move(callback);
}

//! Sets expected ticks count, representing progress of a computation.

void ProgressHandler::setMaxTicksCount(size_t value)
{
    reset();
    m_max_ticks_count = value;
}

bool ProgressHandler::has_interrupt_request() const
{
    return m_interrupt_request;
}

//! Increment number of completed computation steps. Performs callback to inform
//! subscriber about current progress (in percents) and retrieves interrupt request flag.

void ProgressHandler::setCompletedTicks(size_t value)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_completed_ticks += value;
    if (m_completed_ticks > m_max_ticks_count)
        m_max_ticks_count = m_completed_ticks + 1;
    int percentage_done = static_cast<int>(100.0 * m_completed_ticks / m_max_ticks_count);
    m_interrupt_request = m_runner_callback ? m_runner_callback(percentage_done) : m_interrupt_request;
}

//! Resets progress.

void ProgressHandler::reset()
{
    m_interrupt_request = false;
    m_completed_ticks = 0;
}
