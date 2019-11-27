// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/model/compounditem.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>

using namespace ModelView;

class ChildrenStrategiesTest : public ::testing::Test
{
public:
    ~ChildrenStrategiesTest();

    //! Helper class with two properties and one top level item on board.
    class TestItem : public CompoundItem
    {
    public:
        TestItem() : CompoundItem("test")
        {
            addProperty("length", 8.0);
            registerTag(TagInfo::universalTag("children"), /*set_as_default*/ true);
            insertItem(new SessionItem, TagRow::append());
            addProperty("height", 12.0);
        }
        ~TestItem();
    };
};

ChildrenStrategiesTest::~ChildrenStrategiesTest() = default;
ChildrenStrategiesTest::TestItem::~TestItem() = default;

//! Testing AllChildrenStrategy.

TEST_F(ChildrenStrategiesTest, AllChildrenStrategy)
{
    AllChildrenStrategy strategy;

    // nullptr
    auto children = strategy.children(nullptr);
    EXPECT_EQ(children.size(), 0);

    // empty item
    SessionItem item1("model_type");
    children = strategy.children(&item1);
    EXPECT_EQ(children.size(), 0);

    // VectorItem
    VectorItem item2;
    children = strategy.children(&item2);
    EXPECT_EQ(children.size(), 3);

    // CompoundItem
    CompoundItem item3;
    item3.addProperty("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 1);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 3);
}

//! Testing TopItemsStrategy.

TEST_F(ChildrenStrategiesTest, TopItemsStrategy)
{
    TopItemsStrategy strategy;

    // nullptr
    auto children = strategy.children(nullptr);
    EXPECT_EQ(children.size(), 0);

    // empty item
    SessionItem item1("model_type");
    children = strategy.children(&item1);
    EXPECT_EQ(children.size(), 0);

    // VectorItem
    VectorItem item2;
    children = strategy.children(&item2);
    EXPECT_EQ(children.size(), 0);

    // CompoundItem
    CompoundItem item3;
    item3.addProperty("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 0);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 1);
}

//! Testing PropertyItemsStrategy.

TEST_F(ChildrenStrategiesTest, PropertyItemsStrategy)
{
    PropertyItemsStrategy strategy;

    // nullptr
    auto children = strategy.children(nullptr);
    EXPECT_EQ(children.size(), 0);

    // empty item
    SessionItem item1("model_type");
    children = strategy.children(&item1);
    EXPECT_EQ(children.size(), 0);

    // VectorItem
    VectorItem item2;
    children = strategy.children(&item2);
    EXPECT_EQ(children.size(), 3);

    // CompoundItem
    CompoundItem item3;
    item3.addProperty("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 1);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 2);
}
