// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/compounditem.h"

#include "google_test.h"
#include "mvvm/model/customvariants.h"
#include "mvvm/model/itemutils.h"
#include <stdexcept>

using namespace ModelView;

namespace {
const std::string property_name("name");
}

//! Test of CompountItem machinery (property children etc).

class CompoundItemTest : public ::testing::Test {
};

TEST_F(CompoundItemTest, initialState)
{
    CompoundItem item;
    EXPECT_EQ(item.childrenCount(), 0);
}

TEST_F(CompoundItemTest, addIntProperty)
{
    CompoundItem item;

    const int expected = 42;
    auto propertyItem = item.addProperty(property_name, expected);
    EXPECT_TRUE(Utils::HasTag(item, "name"));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsIntVariant(propertyItem->data<QVariant>()));
    EXPECT_EQ(propertyItem->displayName(), property_name);
    EXPECT_EQ(propertyItem->data<int>(), expected);

    EXPECT_FALSE(propertyItem->data<QVariant>(ItemDataRole::LIMITS).isValid());
}

TEST_F(CompoundItemTest, setIntProperty)
{
    CompoundItem item;
    auto propertyItem = item.addProperty(property_name, 41);

    const int expected = 42;
    item.setProperty(property_name, expected);

    EXPECT_EQ(item.property<int>(property_name), expected);
    EXPECT_EQ(propertyItem->data<int>(), expected);
}

TEST_F(CompoundItemTest, addDoubleProperty)
{
    CompoundItem item;

    const double expected = 42.1;
    auto propertyItem = item.addProperty(property_name, expected);
    EXPECT_TRUE(Utils::HasTag(item, property_name));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsDoubleVariant(propertyItem->data<QVariant>()));
    EXPECT_EQ(propertyItem->displayName(), property_name);
    EXPECT_EQ(propertyItem->data<double>(), expected);

    EXPECT_TRUE(propertyItem->data<QVariant>(ItemDataRole::LIMITS).isValid());

    // limits should be "negative 'unlimited' by default
    auto limits = propertyItem->data<RealLimits>(ItemDataRole::LIMITS);
    EXPECT_FALSE(limits.hasLowerLimit());
    EXPECT_FALSE(limits.hasUpperLimit());
}

TEST_F(CompoundItemTest, setDoubleProperty)
{
    CompoundItem item;
    auto propertyItem = item.addProperty(property_name, 41.11);

    const double expected = 42.0;
    item.setProperty(property_name, expected);

    EXPECT_EQ(item.property<double>(property_name), expected);
    EXPECT_EQ(propertyItem->data<double>(), expected);
}

TEST_F(CompoundItemTest, addCharProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty(property_name, "abc");
    EXPECT_TRUE(Utils::HasTag(item, property_name));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsStdStringVariant(propertyItem->data<QVariant>()));
    EXPECT_EQ(propertyItem->data<std::string>(), std::string("abc"));

    EXPECT_FALSE(propertyItem->data<QVariant>(ItemDataRole::LIMITS).isValid());
}

TEST_F(CompoundItemTest, setCharProperty)
{
    CompoundItem item;
    auto propertyItem = item.addProperty(property_name, "aaa");

    const char* expected{"bbb"};
    item.setProperty(property_name, expected);

    EXPECT_EQ(item.property<std::string>(property_name), std::string(expected));
    EXPECT_EQ(propertyItem->data<std::string>(), std::string(expected));
}

TEST_F(CompoundItemTest, addStringProperty)
{
    CompoundItem item;

    auto propertyItem = item.addProperty(property_name, std::string("abc"));
    EXPECT_TRUE(Utils::HasTag(item, property_name));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsStdStringVariant(propertyItem->data<QVariant>()));
    EXPECT_EQ(propertyItem->data<std::string>(), std::string("abc"));

    EXPECT_FALSE(propertyItem->data<QVariant>(ItemDataRole::LIMITS).isValid());
}

TEST_F(CompoundItemTest, setStringProperty)
{
    CompoundItem item;
    auto propertyItem = item.addProperty(property_name, std::string("aaa"));

    const std::string expected{"bbb"};
    item.setProperty(property_name, expected);

    EXPECT_EQ(item.property<std::string>(property_name), expected);
    EXPECT_EQ(propertyItem->data<std::string>(), expected);
}

TEST_F(CompoundItemTest, addBoolProperty)
{
    CompoundItem item;

    const bool expected = true;
    auto propertyItem = item.addProperty(property_name, expected);
    EXPECT_TRUE(Utils::HasTag(item, property_name));

    EXPECT_EQ(propertyItem->modelType(), Constants::PropertyType);
    EXPECT_TRUE(Utils::IsBoolVariant(propertyItem->data<QVariant>()));
    EXPECT_EQ(propertyItem->data<bool>(), expected);

    EXPECT_FALSE(propertyItem->data<QVariant>(ItemDataRole::LIMITS).isValid());
}

TEST_F(CompoundItemTest, setBoolProperty)
{
    CompoundItem item;
    auto propertyItem = item.addProperty(property_name, false);

    const bool expected = true;
    item.setProperty(property_name, expected);

    EXPECT_EQ(item.property<bool>(property_name), expected);
    EXPECT_EQ(propertyItem->data<bool>(), expected);
}

TEST_F(CompoundItemTest, itemAccess)
{
    const std::string tag = "tag";

    // creating parent with one tag
    SessionItem parent;
    parent.registerTag(TagInfo::universalTag(tag));

    // inserting two children
    auto property = parent.insertItem<PropertyItem>({tag, 0});
    EXPECT_TRUE(parent.item<PropertyItem>(tag) == property);
    EXPECT_THROW(parent.item<CompoundItem>(tag), std::runtime_error);
}

TEST_F(CompoundItemTest, itemVectorAccess)
{
    const std::string tag = "tag";

    // creating parent with one tag
    SessionItem parent;
    parent.registerTag(TagInfo::universalTag(tag));

    // inserting two children
    auto property1 = parent.insertItem<PropertyItem>(TagRow::append(tag));
    auto property2 = parent.insertItem<PropertyItem>(TagRow::append(tag));

    auto items = parent.items<PropertyItem>(tag);
    std::vector<PropertyItem*> expected = {property1, property2};
    EXPECT_EQ(items, expected);
    EXPECT_EQ(parent.items<CompoundItem>(tag).size(), 0);
}

//! Tests automatic index addition to default display name.

TEST_F(CompoundItemTest, displayNameIndexAddition)
{
    const std::string tag = "tag";

    // creating parent with one tag
    SessionItem parent;
    parent.registerTag(TagInfo::universalTag(tag));

    // inserting two children
    auto child0 = parent.insertItem<CompoundItem>(TagRow::append(tag));
    auto child1 = parent.insertItem<CompoundItem>(TagRow::append(tag));

    // Default display names of items of the same type should have indices
    EXPECT_EQ(child0->displayName(), Constants::CompoundItemType + "0");
    EXPECT_EQ(child1->displayName(), Constants::CompoundItemType + "1");

    // however, if children have custom display name, they should remain intact
    child0->setDisplayName("Jekyll");
    child1->setDisplayName("Hyde");
    EXPECT_EQ(child0->displayName(), "Jekyll");
    EXPECT_EQ(child1->displayName(), "Hyde");
}

//! Test all children method.
//! Property items are also children.

TEST_F(CompoundItemTest, children)
{
    CompoundItem item;
    EXPECT_TRUE(item.children().empty());
    auto propertyItem = item.addProperty(property_name, false);
    EXPECT_EQ(item.children(), std::vector<SessionItem*>({propertyItem}));
}
