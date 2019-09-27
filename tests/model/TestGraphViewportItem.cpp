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

//! Initial state.

TEST_F(TestGraphViewportItem, initialState)
{
    GraphViewportItem item;
    EXPECT_TRUE(item.getItem(GraphViewportItem::P_XAXIS) != nullptr);
    EXPECT_TRUE(item.getItem(GraphViewportItem::P_YAXIS) != nullptr);
    EXPECT_EQ(item.getItems(GraphViewportItem::T_GRAPHS).size(), 0);
}
