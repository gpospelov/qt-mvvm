#include "google_test.h"
#include "childrenstrategies.h"
#include "sessionitem.h"
#include "vectoritem.h"
#include "propertyitem.h"
#include "compounditem.h"
#include "taginfo.h"

using namespace ModelView;

class TestChildrenStrategies : public ::testing::Test
{
public:
    ~TestChildrenStrategies();
};

TestChildrenStrategies::~TestChildrenStrategies() = default;

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
}
