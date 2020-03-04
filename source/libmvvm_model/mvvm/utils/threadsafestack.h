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

#include <memory>
#include <mutex>
#include <mvvm/core/export.h>
#include <stack>
#include <stdexcept>
#include <thread>

//! @file threadsafestack.h
//! @brief Thread-safe stack borrowed from Anthony Williams, C++ Concurrency in Action, Second
//! edition.

namespace ModelView
{

struct empty_stack : public std::exception {
    const char* what() const noexcept;
};

//! @class threadsafe_stack
//! @brief Thread-safe stack borrowed from Anthony Williams, C++ Concurrency in Action, Second
//! edition.

template <typename T> class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack() {}
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
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pot();
        return res;
    }

    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        value = std::move(data.top());
        data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

} // namespace ModelView

#endif // MVVM_UTILS_THREADSAFESTACK_H
