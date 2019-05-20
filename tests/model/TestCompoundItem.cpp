#include "google_test.h"
#include "test_utils.h"
#include "compounditem.h"
#include "sessionmodel.h"
#include "customvariants.h"
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
    EXPECT_EQ(propertyItem->data(ItemDataRole::DATA).toDouble(), 42.0);
}

TEST_F(TestCompoundItem, addCharProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty<PropertyItem>("name", "abc");
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsStdStringVariant(propertyItem->data(ItemDataRole::DATA)));
    EXPECT_EQ(propertyItem->data(ItemDataRole::DATA).value<std::string>(), std::string("abc"));
}

TEST_F(TestCompoundItem, addDoubleProperty)
{
    CompoundItem item;

    const double expected(42.1);
    auto propertyItem = item.addProperty<PropertyItem>("name", expected);
    EXPECT_TRUE(item.isTag("name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsDoubleVariant(propertyItem->data(ItemDataRole::DATA)));
    EXPECT_EQ(propertyItem->data(ItemDataRole::DATA).toDouble(), expected);

    EXPECT_TRUE(propertyItem->data(ItemDataRole::LIMITS).isValid());
}

TEST_F(TestCompoundItem, itemValue)
{
    CompoundItem item;

    auto propertyItem = item.addProperty<>("height", 42.0);
    EXPECT_TRUE(item.isTag("height"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_EQ(item.getItemValue("height").toDouble(), 42.0);

    // setting value
    double expected(442.0);
    item.setItemValue("height", expected);
    EXPECT_EQ(item.getItemValue("height").toDouble(), expected);
    EXPECT_EQ(propertyItem->data(ItemDataRole::DATA).toDouble(), expected);
}

