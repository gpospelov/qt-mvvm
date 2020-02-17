// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/viewmodel/refviewmodel.h>

using namespace ModelView;

//! Tests for RefViewModel class.

class RefViewModelTest : public ::testing::Test
{
public:
    ~RefViewModelTest();
};

RefViewModelTest::~RefViewModelTest() = default;

TEST_F(RefViewModelTest, initialState)
{
    RefViewModel viewmodel;
    EXPECT_EQ(1, 1);
}
