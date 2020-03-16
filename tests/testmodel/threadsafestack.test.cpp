// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <future>
#include <mvvm/utils/threadsafestack.h>

using namespace ModelView;

//! Testing AxisItems.

class ThreadSafeStackTest : public ::testing::Test
{
public:
    ~ThreadSafeStackTest();
};

ThreadSafeStackTest::~ThreadSafeStackTest() = default;

//! Checking stack initial state (single thread mode).

TEST_F(ThreadSafeStackTest, initialState)
{
    threadsafe_stack<int> stack;
    EXPECT_TRUE(stack.empty());
    int value;
    EXPECT_FALSE(stack.try_pop(value));

    auto sh_value = stack.try_pop();
    EXPECT_FALSE(sh_value);
}

//! Push and then pop (single thread mode).

TEST_F(ThreadSafeStackTest, pushAndPop)
{
    threadsafe_stack<int> stack;

    stack.push(42);
    EXPECT_FALSE(stack.empty());
    int value(0);
    EXPECT_TRUE(stack.try_pop(value));
    EXPECT_EQ(value, 42);

    stack.push(43);
    auto result = stack.wait_and_pop();
    EXPECT_EQ(*result.get(), 43);
}

//! Update top value (single thread mode).

TEST_F(ThreadSafeStackTest, updateTop)
{
    threadsafe_stack<int> stack;

    // update of empty stack means simple appearance of value
    stack.update_top(42);
    EXPECT_FALSE(stack.empty());
    int value(0);
    EXPECT_TRUE(stack.try_pop(value));
    EXPECT_EQ(value, 42);

    // updating value
    stack.push(43);
    stack.update_top(44);
    auto result = stack.wait_and_pop();
    EXPECT_EQ(*result.get(), 44);

    // shouldn't be more values
    auto sh_value = stack.try_pop();
    EXPECT_FALSE(sh_value);
}

//! Push and pop in concurrent mode.
//! Test is borrowed from Anthony Williams, C++ Concurrency in Action, Second edition.

TEST_F(ThreadSafeStackTest, concurentPushAndPop)
{
    threadsafe_stack<int> stack;
    std::promise<void> go, push_ready_for_test, pop_ready_for_test;
    std::shared_future<void> ready(go.get_future());
    std::future<void> push_done;
    std::future<std::shared_ptr<int>> pop_done;

    try {
        // starting pushing thread
        push_done = std::async(std::launch::async, [&stack, ready, &push_ready_for_test]() {
            push_ready_for_test.set_value();
            ready.wait();
            stack.push(42);
        });

        // starting pop thread
        pop_done = std::async(std::launch::async, [&stack, ready, &pop_ready_for_test]() {
            pop_ready_for_test.set_value();
            ready.wait();
            return stack.wait_and_pop();
        });

        // waiting for threads being prepared for racing
        push_ready_for_test.get_future().wait();
        pop_ready_for_test.get_future().wait();

        // starting concurrent push and pop
        go.set_value();

        // checking result
        push_done.get(); // making sure pushing thread has finished

        EXPECT_EQ(*pop_done.get(), 42);
        EXPECT_TRUE(stack.empty());

    } catch (...) {
        go.set_value();
        throw;
    }
}

//! Explicitely terminate waiting (concurrent mode).

TEST_F(ThreadSafeStackTest, concurentStopWaiting)
{
    threadsafe_stack<int> stack;
    std::promise<void> go, pop_ready_for_test;
    std::shared_future<void> ready(go.get_future());
    std::future<std::shared_ptr<int>> pop_done;

    try {
        // starting pop thread
        pop_done = std::async(std::launch::async, [&stack, ready, &pop_ready_for_test]() {
            pop_ready_for_test.set_value();
            ready.wait();
            return stack.wait_and_pop();
        });

        // waiting for threads being prepared for racing
        pop_ready_for_test.get_future().wait();

        // starting waiting on empty stack
        go.set_value();

        // stopping waiting
        stack.stop();

        // stopping stack will raise exception
        EXPECT_THROW(*pop_done.get(), empty_stack);
        EXPECT_TRUE(stack.empty());

    } catch (...) {
        go.set_value();
        throw;
    }
}
