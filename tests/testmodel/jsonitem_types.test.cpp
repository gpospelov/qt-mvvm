// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/serialization/jsonitem_types.h>

using namespace ModelView;

//! Testing json related flags.

class JsonItemTypesTest : public ::testing::Test
{
public:
    ~JsonItemTypesTest();
};

JsonItemTypesTest::~JsonItemTypesTest() = default;

TEST_F(JsonItemTypesTest, initialState)
{
    EXPECT_FALSE(hasFlag(ConverterFlags::COPY_MODE, ConverterFlags::USE_JSON_ID));
    EXPECT_TRUE((ConverterFlags::COPY_MODE & ConverterFlags::USE_JSON_ID) == ConverterFlags::NONE);
}
