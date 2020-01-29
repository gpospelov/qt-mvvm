// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "layeritems.h"
#include "test_utils.h"

using namespace ModelView;

//! Test of CompountItem machinery (property children etc).

class LayerItemsTest : public ::testing::Test
{
public:
    ~LayerItemsTest();
};

LayerItemsTest::~LayerItemsTest() = default;

TEST_F(LayerItemsTest, initialState)
{
    EXPECT_EQ(1, 1);
}
