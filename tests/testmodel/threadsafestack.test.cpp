// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/utils/threadsafestack.h>

using namespace ModelView;

//! Testing AxisItems.

class ThreadSafeStackTest : public ::testing::Test
{
public:
    ~ThreadSafeStackTest();
};

ThreadSafeStackTest::~ThreadSafeStackTest() = default;

//! No threads. Checking stack initial state.

TEST_F(ThreadSafeStackTest, noThreadsInitialState)
{
    threadsafe_stack<int> stack;
    EXPECT_TRUE(stack.empty());
    int value;
    EXPECT_THROW(stack.pop(value), empty_stack);
}

//! No threads. Checking stack initial state.

TEST_F(ThreadSafeStackTest, noThreadsPushAndPop)
{
    threadsafe_stack<int> stack;

    stack.push(42);
    EXPECT_FALSE(stack.empty());
    int value(0);
    EXPECT_NO_THROW(stack.pop(value));
    EXPECT_EQ(value, 42);

    stack.push(43);
    auto result = stack.pop();
    EXPECT_EQ(*result.get(), 43);
}
