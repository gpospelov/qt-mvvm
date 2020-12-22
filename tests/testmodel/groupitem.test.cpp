// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/groupitem.h"

#include "google_test.h"
#include <stdexcept>

using namespace ModelView;

//! Testing GroupItem class.

class GroupItemTest : public ::testing::Test {
};

TEST_F(GroupItemTest, initialState)
{
    GroupItem item;
    EXPECT_EQ(item.currentIndex(), -1);
    EXPECT_EQ(item.currentItem(), nullptr);
    EXPECT_EQ(item.currentType(), "");
    EXPECT_TRUE(item.hasData());
    EXPECT_TRUE(item.children().empty());
    EXPECT_THROW(item.setCurrentType("abc"), std::runtime_error);
}
