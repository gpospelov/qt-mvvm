#include "google_test.h"
#include "viewitem.h"

using namespace ModelView;

class TestViewItem : public ::testing::Test
{
public:
    ~TestViewItem();
};

TestViewItem::~TestViewItem() = default;

TEST_F(TestViewItem, initialState)
{
    EXPECT_EQ(1, 1);
}
