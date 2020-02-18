// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/utils/containerutils.h>

using namespace ModelView;

//! Tests of container utils.

class ContainerUtilsTest : public ::testing::Test
{
public:
    ~ContainerUtilsTest();
};

ContainerUtilsTest::~ContainerUtilsTest() = default;

TEST_F(ContainerUtilsTest, IndexOfItem)
{
    std::vector<int> vv{1, 7, 5};
    EXPECT_EQ(Utils::IndexOfItem(vv, 1), 0);
    EXPECT_EQ(Utils::IndexOfItem(vv, 10), -1);
    EXPECT_EQ(Utils::IndexOfItem(vv, 5), 2);
    EXPECT_EQ(Utils::IndexOfItem(vv.begin(), vv.end(), 7), 1);
}
