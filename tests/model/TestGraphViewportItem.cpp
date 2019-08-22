#include "google_test.h"
#include "graphviewportitem.h"

using namespace ModelView;

//! Testing AxesItems.

class TestGraphViewportItem : public ::testing::Test
{
public:
    ~TestGraphViewportItem();
};

TestGraphViewportItem::~TestGraphViewportItem() = default;

//! Initial state

TEST_F(TestGraphViewportItem, initialState)
{
    EXPECT_EQ(1,1);
}
