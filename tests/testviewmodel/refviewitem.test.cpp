// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"

using namespace ModelView;

//! Tests for RefViewItem class.

class RefViewItemTest : public ::testing::Test
{
public:
    ~RefViewItemTest();
};

RefViewItemTest::~RefViewItemTest() = default;

TEST_F(RefViewItemTest, initialState)
{
    EXPECT_EQ(1, 1);
}
