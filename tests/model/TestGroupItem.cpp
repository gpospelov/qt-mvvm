#include "google_test.h"
#include "groupitem.h"

using namespace ModelView;

//! Testing GroupItem class.

class TestGroupItem : public ::testing::Test
{
public:
    ~TestGroupItem();
};

TestGroupItem::~TestGroupItem() = default;

TEST_F(TestGroupItem, initialState)
{
    GroupItem item;
    EXPECT_EQ(item.currentIndex(), -1);
    EXPECT_EQ(item.currentItem(), nullptr);
    EXPECT_EQ(item.currentType(), "");
    EXPECT_FALSE(item.data(ItemDataRole::DATA).isValid());
    EXPECT_TRUE(item.children().empty());

    EXPECT_THROW(item.setCurrentType("abc"), std::runtime_error);
}
