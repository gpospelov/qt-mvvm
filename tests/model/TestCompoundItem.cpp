#include "compounditem.h"
#include "customvariants.h"
#include "google_test.h"
#include "sessionmodel.h"
#include "test_utils.h"
#include <memory>
#include <stdexcept>

using namespace ModelView;

//! Test of CompountItem machinery (property children etc).

class TestCompoundItem : public ::testing::Test
{
public:
    ~TestCompoundItem();
};

TestCompoundItem::~TestCompoundItem() = default;

TEST_F(TestCompoundItem, initialState)
{
    CompoundItem item;
    EXPECT_EQ(item.childrenCount(), 0);
}

TEST_F(TestCompoundItem, addIntProperty)
{
    CompoundItem item;

    const int expected = 42;
    auto propertyItem = item.addProperty("name", expected);
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsIntVariant(propertyItem->data()));
    EXPECT_EQ(propertyItem->displayName(), "name");
    EXPECT_EQ(propertyItem->data().toInt(), expected);
    EXPECT_EQ(propertyItem->data().value<int>(), expected);

    EXPECT_FALSE(propertyItem->data(ItemDataRole::LIMITS).isValid());
}

TEST_F(TestCompoundItem, addDoubleProperty)
{
    CompoundItem item;

    const double expected = 42.1;
    auto propertyItem = item.addProperty("name", expected);
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsDoubleVariant(propertyItem->data()));
    EXPECT_EQ(propertyItem->displayName(), "name");
    EXPECT_EQ(propertyItem->data().toDouble(), expected);
    EXPECT_EQ(propertyItem->data().value<double>(), expected);

    EXPECT_TRUE(propertyItem->data(ItemDataRole::LIMITS).isValid());
}

TEST_F(TestCompoundItem, addCharProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty("name", "abc");
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsStdStringVariant(propertyItem->data()));
    EXPECT_EQ(propertyItem->data().value<std::string>(), std::string("abc"));

    EXPECT_FALSE(propertyItem->data(ItemDataRole::LIMITS).isValid());
}

TEST_F(TestCompoundItem, addBoolProperty)
{
    CompoundItem item;

    const bool expected = true;
    auto propertyItem = item.addProperty("name", expected);
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsBoolVariant(propertyItem->data()));
    EXPECT_EQ(propertyItem->data().value<bool>(), expected);

    EXPECT_FALSE(propertyItem->data(ItemDataRole::LIMITS).isValid());
}


TEST_F(TestCompoundItem, setProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty("height", 42.0);
    EXPECT_TRUE(item.isTag("height"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_EQ(item.property("height").toDouble(), 42.0);

    // setting value
    double expected(442.0);
    item.setProperty("height", expected);
    EXPECT_EQ(item.property("height").toDouble(), expected);
    EXPECT_EQ(propertyItem->data().toDouble(), expected);
}

TEST_F(TestCompoundItem, itemAccess)
{
    const std::string tag = "tag";

    // creating parent with one tag
    SessionItem parent;
    parent.registerTag(TagInfo::universalTag(tag));

    // inserting two children
    auto property = new PropertyItem;
    parent.insertItem(property, {tag, 0});

    EXPECT_TRUE(parent.item<PropertyItem>(tag) == property);
    EXPECT_THROW(parent.item<CompoundItem>(tag), std::runtime_error);
}

TEST_F(TestCompoundItem, itemVectorAccess)
{
    const std::string tag = "tag";

    // creating parent with one tag
    SessionItem parent;
    parent.registerTag(TagInfo::universalTag(tag));

    // inserting two children
    auto property1 = new PropertyItem;
    auto property2 = new PropertyItem;
    parent.insertItem(property1, TagRow::append(tag));
    parent.insertItem(property2, TagRow::append(tag));

    auto items = parent.items<PropertyItem>(tag);
    std::vector<PropertyItem*> expected = {property1, property2};
    EXPECT_EQ(items, expected);
    EXPECT_EQ(parent.items<CompoundItem>(tag).size(), 0);
}

//! Tests automatic index addition to default display name.

TEST_F(TestCompoundItem, displayNameIndexAddition)
{
    const std::string tag = "tag";

    // creating parent with one tag
    SessionItem parent;
    parent.registerTag(TagInfo::universalTag(tag));

    // inserting two children
    auto child0 = new CompoundItem;
    parent.insertItem(child0, TagRow::append(tag));
    auto child1 = new CompoundItem;
    parent.insertItem(child1, TagRow::append(tag));

    // Default display names of items of the same type should have indices
    EXPECT_EQ(child0->displayName(), Constants::CompoundItemType + "0");
    EXPECT_EQ(child1->displayName(), Constants::CompoundItemType + "1");

    // however, if children have custom display name, they should remain intact
    child0->setDisplayName("Jekyll");
    child1->setDisplayName("Hyde");
    EXPECT_EQ(child0->displayName(), "Jekyll");
    EXPECT_EQ(child1->displayName(), "Hyde");
}
