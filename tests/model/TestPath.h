#include <gtest/gtest.h>
#include "path.h"
#include <memory>

class TestPath : public ::testing::Test
{
public:
    ~TestPath();
};

TestPath::~TestPath() = default;

TEST_F(TestPath, initialState)
{
    Path path;
    EXPECT_TRUE(path.str().empty());
}

TEST_F(TestPath, append)
{
    Path path;
    path.append(1);
    EXPECT_EQ(path.str(), "1");

    path.append(2);
    EXPECT_EQ(path.str(), "1,2");
}
