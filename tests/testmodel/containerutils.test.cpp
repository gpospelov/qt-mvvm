// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <complex>
#include <mvvm/model/sessionitem.h>
#include <mvvm/utils/containerutils.h>

using namespace ModelView;

//! Tests of container utils.

class ContainerUtilsTest : public ::testing::Test
{
public:
    ~ContainerUtilsTest();
};

ContainerUtilsTest::~ContainerUtilsTest() = default;

TEST_F(ContainerUtilsTest, isUniquePtr)
{
    EXPECT_FALSE(Utils::is_unique_ptr<int>::value);
    EXPECT_TRUE(Utils::is_unique_ptr<std::unique_ptr<int>>::value);
}

TEST_F(ContainerUtilsTest, IndexOfItem)
{
    // searching in vector of integers
    std::vector<int> vv{1, 7, 5};
    EXPECT_EQ(Utils::IndexOfItem(vv, 1), 0);
    EXPECT_EQ(Utils::IndexOfItem(vv, 10), -1);
    EXPECT_EQ(Utils::IndexOfItem(vv, 5), 2);
    EXPECT_EQ(Utils::IndexOfItem(vv.begin(), vv.end(), 7), 1);

    // searching in vector of SessionItem's
    std::vector<SessionItem*> items{new SessionItem, new SessionItem, new SessionItem};
    SessionItem other;
    EXPECT_EQ(Utils::IndexOfItem(items, items[0]), 0);
    EXPECT_EQ(Utils::IndexOfItem(items, items[1]), 1);
    EXPECT_EQ(Utils::IndexOfItem(items, items[2]), 2);
    EXPECT_EQ(Utils::IndexOfItem(items, &other), -1);
    for (auto x : items)
        delete x;

    // searching in vector of unique_ptr
    std::vector<std::unique_ptr<SessionItem>> unique_items;
    unique_items.emplace_back(std::make_unique<SessionItem>());
    unique_items.emplace_back(std::make_unique<SessionItem>());
    EXPECT_EQ(Utils::IndexOfItem(unique_items, unique_items[0].get()), 0);
    EXPECT_EQ(Utils::IndexOfItem(unique_items, unique_items[1].get()), 1);
    EXPECT_EQ(Utils::IndexOfItem(unique_items, &other), -1);
}

TEST_F(ContainerUtilsTest, Real)
{
    std::vector<std::complex<double>> data = {{1.0, 10.0}, {2.0, 20.0}};
    EXPECT_EQ(Utils::Real(data), (std::vector<double>{1.0, 2.0}));
    EXPECT_EQ(Utils::Imag(data), (std::vector<double>{10.0, 20.0}));
}

TEST_F(ContainerUtilsTest, UniqueWithOrder)
{
    std::vector<int> data = {1, 42, 1, 6, 43, 6};
    EXPECT_EQ(Utils::UniqueWithOrder(data), (std::vector<int>{1, 42, 6, 43}));
}

TEST_F(ContainerUtilsTest, Contains)
{
    std::vector<int> data = {1, 42, 1, 6, 43, 6};
    EXPECT_TRUE(Utils::Contains(data, 42));
    EXPECT_FALSE(Utils::Contains(data, 99));
}
