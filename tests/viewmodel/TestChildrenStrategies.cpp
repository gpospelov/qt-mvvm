#include "google_test.h"
#include "childrenstrategies.h"
#include "compounditem.h"
#include "propertyitem.h"
#include "sessionitem.h"
#include "taginfo.h"
#include "vectoritem.h"

using namespace ModelView;

class TestChildrenStrategies : public ::testing::Test
{
public:
    ~TestChildrenStrategies();

    //! Helper class with two properties and one top level item on board.
    class TestItem : public CompoundItem
    {
    public:
        TestItem() : CompoundItem("test")
        {
            addProperty<PropertyItem>("length", 8.0);
            registerTag(TagInfo::universalTag("children"), /*set_as_default*/ true);
            insertItem(new SessionItem);
            addProperty<PropertyItem>("height", 12.0);
        }
        ~TestItem();
    };
};

TestChildrenStrategies::~TestChildrenStrategies() = default;
TestChildrenStrategies::TestItem::~TestItem() = default;

//! Testing AllChildrenStrategy.

TEST_F(TestChildrenStrategies, AllChildrenStrategy)
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
    item3.addProperty<PropertyItem>("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 1);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 3);
}

//! Testing TopItemsStrategy.

TEST_F(TestChildrenStrategies, TopItemsStrategy)
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
    item3.addProperty<PropertyItem>("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 0);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 1);
}

//! Testing AllChildrenStrategy.

TEST_F(TestChildrenStrategies, PropertyItemsStrategy)
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
    item3.addProperty<PropertyItem>("height", 42.0);
    children = strategy.children(&item3);
    EXPECT_EQ(children.size(), 1);

    // TestItem
    TestItem item4;
    children = strategy.children(&item4);
    EXPECT_EQ(children.size(), 2);
}
