// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonitem_types.h"

#include "google_test.h"

using namespace ModelView;

//! Testing json related flags.

class JsonItemTypesTest : public ::testing::Test {
};

TEST_F(JsonItemTypesTest, isRegenerateIdWhenBackFromJson)
{
    EXPECT_FALSE(isRegenerateIdWhenBackFromJson(ConverterMode::none));
    EXPECT_FALSE(isRegenerateIdWhenBackFromJson(ConverterMode::clone));
    EXPECT_TRUE(isRegenerateIdWhenBackFromJson(ConverterMode::copy));
    EXPECT_FALSE(isRegenerateIdWhenBackFromJson(ConverterMode::project));
}

TEST_F(JsonItemTypesTest, isRebuildItemDataAndTagFromJson)
{
    EXPECT_TRUE(isRebuildItemDataAndTagFromJson(ConverterMode::none));
    EXPECT_TRUE(isRebuildItemDataAndTagFromJson(ConverterMode::clone));
    EXPECT_TRUE(isRebuildItemDataAndTagFromJson(ConverterMode::copy));
    EXPECT_FALSE(isRebuildItemDataAndTagFromJson(ConverterMode::project));
}
