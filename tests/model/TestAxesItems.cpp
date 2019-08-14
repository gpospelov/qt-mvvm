#include "google_test.h"
#include "axesitems.h"

using namespace ModelView;

//! Testing AxesItems.

class TestAxesItems : public ::testing::Test
{
public:
    ~TestAxesItems();
};

TestAxesItems::~TestAxesItems() = default;

//! Callback container notifies single widget. Check if removal of widget disables notifications.

TEST_F(TestAxesItems, fixedBinAxisFactory)
{
    auto axis = FixedBinAxisItem::create(10, 1.0, 2.0);

    EXPECT_EQ(axis->getItem(FixedBinAxisItem::P_NBINS)->data(ItemDataRole::DATA), 10);
    EXPECT_EQ(axis->getItem(FixedBinAxisItem::P_MIN)->data(ItemDataRole::DATA), 1.0);
    EXPECT_EQ(axis->getItem(FixedBinAxisItem::P_MAX)->data(ItemDataRole::DATA), 2.0);
}
