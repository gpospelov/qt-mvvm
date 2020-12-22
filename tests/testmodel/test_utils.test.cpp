// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "test_utils.h"

#include "google_test.h"

using TestUtils::toVector;

//! Testing functions in test_utils.

class TestUtilsTest : public ::testing::Test {
};

//! Testing toVector function.

TEST_F(TestUtilsTest, toVector)
{
    std::vector<int> expected_int = {1, 2, 3};
    EXPECT_EQ(toVector<int>(1, 2, 3), expected_int);

    std::vector<double> expected_double = {1.1, 2.2, 3.3};
    EXPECT_EQ(toVector<double>(1.1, 2.2, 3.3), expected_double);

    std::vector<std::string> expected_string = {"a", "bb", "ccc"};
    EXPECT_EQ(toVector<std::string>("a", "bb", "ccc"), expected_string);
}
