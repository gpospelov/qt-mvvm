// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/containeritem.h"

#include "google_test.h"
#include <memory>

using namespace ModelView;

//! Test of ContainerItem.

class ContainerItemTest : public ::testing::Test {
};

TEST_F(ContainerItemTest, initialState)
{
    ContainerItem item;
    EXPECT_EQ(item.size(), 0);
    EXPECT_TRUE(item.empty());
}

TEST_F(ContainerItemTest, isEmpty)
{
    ContainerItem item;
    item.insertItem<PropertyItem>({"", 0});
    EXPECT_EQ(item.size(), 1);
    EXPECT_FALSE(item.empty());
}
