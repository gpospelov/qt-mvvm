// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/utils/numericutils.h"

#include "google_test.h"
#include <cmath>

using namespace ModelView;

class NumericUtilsTest : public ::testing::Test {
};

TEST_F(NumericUtilsTest, areAlmostEqual)
{
    EXPECT_TRUE(Utils::AreAlmostEqual(0.0, 0.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(1.0, 1.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(10.0 / 100.0, 100.0 / 1000.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(std::sin(0.0), 0.0));
    EXPECT_FALSE(Utils::AreAlmostEqual(std::cos(0.0), 0.0));
}
