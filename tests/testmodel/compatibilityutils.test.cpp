// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/serialization/compatibilityutils.h>
#include <mvvm/model/mvvm_types.h>

using namespace ModelView;

//! Test of CompatibilityUtilsTest.

class CompatibilityUtilsTest : public ::testing::Test
{
public:
    ~CompatibilityUtilsTest();
};

CompatibilityUtilsTest::~CompatibilityUtilsTest() = default;

//! Testing CombineItemData when both sources are empty.

TEST_F(CompatibilityUtilsTest, combineItemDataBothEmpty)
{
    SessionItemData runtime;
    SessionItemData persistent;

    auto result = Compatibility::CombineItemData(runtime, persistent);

    EXPECT_TRUE(result->roles().empty());
}

//! Testing CombineItemData when `runtime` source has data, and `persistent` source is empty.

TEST_F(CompatibilityUtilsTest, combineItemDataPersistentEmpty)
{
    SessionItemData runtime;
    runtime.setData(QVariant::fromValue(std::string("abc")), ItemDataRole::IDENTIFIER);
    runtime.setData(QVariant::fromValue(42), ItemDataRole::DATA);

    SessionItemData persistent;

    auto result = Compatibility::CombineItemData(runtime, persistent);

    std::vector<int> expected{ItemDataRole::IDENTIFIER, ItemDataRole::DATA};
    EXPECT_EQ(result->roles(), expected);
    EXPECT_EQ(result->data(ItemDataRole::IDENTIFIER).value<std::string>(), std::string("abc"));
    EXPECT_EQ(result->data(ItemDataRole::DATA).value<int>(), 42);
}

//! Testing CombineItemData when `persistent` source has data, and `runtime` source is empty.

TEST_F(CompatibilityUtilsTest, combineItemDataRuntimeEmpty)
{
    SessionItemData runtime;

    SessionItemData persistent;
    persistent.setData(QVariant::fromValue(std::string("abc")), ItemDataRole::IDENTIFIER);
    persistent.setData(QVariant::fromValue(42), ItemDataRole::DATA);

    auto result = Compatibility::CombineItemData(runtime, persistent);

    std::vector<int> expected{ItemDataRole::IDENTIFIER, ItemDataRole::DATA};
    EXPECT_EQ(result->roles(), expected);
    EXPECT_EQ(result->data(ItemDataRole::IDENTIFIER).value<std::string>(), std::string("abc"));
    EXPECT_EQ(result->data(ItemDataRole::DATA).value<int>(), 42);
}

//! Testing CombineItemData when `persistent` source and `runtime` both have data (identifier and
//! data roles). Additionally, `runtime` has tooltip roles.
//! As a result `indetifier` and `data` roles have to be taken from `persistent` source, `tooltip`
//! from runtime source.

TEST_F(CompatibilityUtilsTest, combineItemDataTypicalScenario)
{
    SessionItemData runtime;
    runtime.setData(QVariant::fromValue(std::string("abc")), ItemDataRole::IDENTIFIER);
    runtime.setData(QVariant::fromValue(42), ItemDataRole::DATA);
    runtime.setData(QVariant::fromValue(std::string("tooltip")), ItemDataRole::TOOLTIP);

    SessionItemData persistent; // order is different intentionally
    persistent.setData(QVariant::fromValue(43), ItemDataRole::DATA);
    persistent.setData(QVariant::fromValue(std::string("def")), ItemDataRole::IDENTIFIER);

    auto result = Compatibility::CombineItemData(runtime, persistent);

    std::vector<int> expected{ItemDataRole::IDENTIFIER, ItemDataRole::DATA, ItemDataRole::TOOLTIP};
    EXPECT_EQ(result->roles(), expected);
    // roles from `persistent` source
    EXPECT_EQ(result->data(ItemDataRole::IDENTIFIER).value<std::string>(), std::string("def"));
    EXPECT_EQ(result->data(ItemDataRole::DATA).value<int>(), 43);
    // roles from `runtime` source
    EXPECT_EQ(result->data(ItemDataRole::TOOLTIP).value<std::string>(), std::string("tooltip"));
}

//! Testing IsCompatibleSingleProperty.

TEST_F(CompatibilityUtilsTest, IsCompatibleSingleProperty)
{
    const std::string name("tag");
    TagInfo tag = TagInfo::propertyTag("thickness", Constants::PropertyType);
    SessionItemContainer container(tag);

    // to be compatible, container should have PropertyItem in it already
    EXPECT_FALSE(Compatibility::IsCompatibleSinglePropertyTag(container, tag));

    EXPECT_TRUE(container.insertItem(new PropertyItem, 0));
    EXPECT_TRUE(Compatibility::IsCompatibleSinglePropertyTag(container, tag));
}
