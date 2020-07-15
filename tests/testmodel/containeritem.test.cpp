// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <memory>
#include <mvvm/standarditems/containeritem.h>

using namespace ModelView;

//! Test of ContainerItem.

class ContainerItemTest : public ::testing::Test
{
public:
    ~ContainerItemTest();
};

ContainerItemTest::~ContainerItemTest() = default;

TEST_F(ContainerItemTest, initialState)
{
    ContainerItem item;
    EXPECT_EQ(item.size(), 0);
    EXPECT_TRUE(item.empty());
}

TEST_F(ContainerItemTest, isEmpty)
{
    ContainerItem item;

    // inserting two children
    auto property = new PropertyItem;
    item.insertItem(property, {"", 0});

    EXPECT_EQ(item.size(), 1);
    EXPECT_FALSE(item.empty());
}
