// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/model/groupitem.h>

using namespace ModelView;

//! Testing GroupItem class.

class GroupItemTest : public ::testing::Test
{
public:
    ~GroupItemTest();
};

GroupItemTest::~GroupItemTest() = default;

TEST_F(GroupItemTest, initialState)
{
    GroupItem item;
    EXPECT_EQ(item.currentIndex(), -1);
    EXPECT_EQ(item.currentItem(), nullptr);
    EXPECT_EQ(item.currentType(), "");
    EXPECT_FALSE(item.data().isValid());
    EXPECT_TRUE(item.children().empty());

    EXPECT_THROW(item.setCurrentType("abc"), std::runtime_error);
}
