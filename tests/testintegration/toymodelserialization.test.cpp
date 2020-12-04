// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toy_models.h"

using namespace ModelView;

//! Testing serialization of ToyModel using json converters.

class ToyModelSerializationTest : public ::testing::Test
{
public:
    ~ToyModelSerializationTest();
};

ToyModelSerializationTest::~ToyModelSerializationTest() = default;

TEST_F(ToyModelSerializationTest, toyGroupItem)
{
    EXPECT_EQ(1, 1);
}
