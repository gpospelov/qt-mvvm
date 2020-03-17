// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/utils/progresshandler.h>

using namespace ModelView;

class ProgressHandlerTest : public ::testing::Test
{
public:
    ~ProgressHandlerTest();
};

ProgressHandlerTest::~ProgressHandlerTest() = default;

TEST_F(ProgressHandlerTest, initialState)
{
    ProgressHandler handler;
    EXPECT_FALSE(handler.has_interrupt_request());
}

TEST_F(ProgressHandlerTest, fullConstructor)
{
    size_t max_ticks = 1000;
    int progress{0};
    auto on_progress_change = [&progress](int value) {
        progress = value;
        return false;
    };

    ProgressHandler handler(on_progress_change, max_ticks);

    handler.setCompletedTicks(100);
    EXPECT_FALSE(handler.has_interrupt_request());
    EXPECT_EQ(progress, 10);

    handler.setCompletedTicks(900);
    EXPECT_FALSE(handler.has_interrupt_request());
    EXPECT_EQ(progress, 100); // reports value in percents
}

TEST_F(ProgressHandlerTest, interruptRequest)
{
    size_t max_ticks = 1000;
    int progress{0};
    auto on_progress_change = [&progress](int value) {
        progress = value;
        return true;
    };

    ProgressHandler handler(on_progress_change, max_ticks);

    handler.setCompletedTicks(1000);
    EXPECT_TRUE(handler.has_interrupt_request());
    EXPECT_EQ(progress, 100); // reports value in percents

    // checking reset
    handler.reset();
    EXPECT_FALSE(handler.has_interrupt_request());
    handler.setCompletedTicks(100);
    EXPECT_EQ(progress, 10); // reports value in percents
}
