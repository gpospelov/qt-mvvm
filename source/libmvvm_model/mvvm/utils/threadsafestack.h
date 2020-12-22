// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_THREADSAFESTACK_H
#define MVVM_UTILS_THREADSAFESTACK_H

#include "mvvm/model_export.h"
#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <stack>
#include <stdexcept>
#include <thread>

//! @file threadsafestack.h
//! @brief Thread-safe stack borrowed from Anthony Williams, C++ Concurrency in Action, Second
//! edition.

namespace ModelView {

struct empty_stack : public std::exception {
    const char* what() const noexcept { return "Empty stack"; }
};

//! @class threadsafe_stack
//! @brief Thread-safe stack borrowed from Anthony Williams, C++ Concurrency in Action, Second
//! edition.

template <typename T> class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;
    std::condition_variable data_condition;
    std::atomic<bool> in_waiting_state{true};

public:
    threadsafe_stack() {}
    ~threadsafe_stack() { stop(); }
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(m);
        data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack& other) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
        data_condition.notify_one();
    }

    //! Updates top value in a stack.

    void update_top(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (!data.empty())
            data.pop();
        data.push(std::move(new_value));
        data_condition.notify_one();
    }

    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lock(m);
        data_condition.wait(lock, [this] { return !data.empty() || !in_waiting_state; });
        if (data.empty())
            throw empty_stack();
        value = std::move(data.top());
        data.pop();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lock(m);
        data_condition.wait(lock, [this] { return !data.empty() || !in_waiting_state; });
        if (data.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            return false;
        value = std::move(data.top());
        data.pop();
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

    //! Terminates waiting in wait_and_pop methods.

    void stop()
    {
        std::lock_guard<std::mutex> lock(m);
        in_waiting_state = false;
        data_condition.notify_all();
    }
};

} // namespace ModelView

#endif // MVVM_UTILS_THREADSAFESTACK_H
