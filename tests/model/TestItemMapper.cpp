#include "google_test.h"
#include "itemmapper.h"

using namespace ModelView;

class TestItemMapper : public ::testing::Test
{
public:
    ~TestItemMapper();
};

TestItemMapper::~TestItemMapper() = default;

TEST_F(TestItemMapper, initialState)
{

    EXPECT_EQ(1, 1);
}
