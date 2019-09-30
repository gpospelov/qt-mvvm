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

TEST_F(TestCompoundItem, addProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty<PropertyItem>("height", 42.0);
    EXPECT_TRUE(item.isTag("height"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_EQ(propertyItem->displayName(), "height");
    EXPECT_EQ(propertyItem->data().toDouble(), 42.0);
}

TEST_F(TestCompoundItem, addCharProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty<PropertyItem>("name", "abc");
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsStdStringVariant(propertyItem->data()));
    EXPECT_EQ(propertyItem->data().value<std::string>(), std::string("abc"));
}

TEST_F(TestCompoundItem, addDoubleProperty)
{
    CompoundItem item;

    const double expected(42.1);
    auto propertyItem = item.addProperty<PropertyItem>("name", expected);
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsDoubleVariant(propertyItem->data()));
    EXPECT_EQ(propertyItem->data().toDouble(), expected);

    EXPECT_TRUE(propertyItem->data(ItemDataRole::LIMITS).isValid());
}

TEST_F(TestCompoundItem, setProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty<>("height", 42.0);
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
    parent.insertItem(property, tag);

    EXPECT_TRUE(&parent.item<PropertyItem>(tag) == property);
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
    parent.insertItem(property1, tag);
    parent.insertItem(property2, tag);

    auto items = parent.items<PropertyItem>(tag);
    std::vector<PropertyItem*> expected = {property1, property2};
    EXPECT_EQ(items, expected);
    EXPECT_EQ(parent.items<CompoundItem>(tag).size(), 0);
}
