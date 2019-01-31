#include "google_test.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "ItemMockWidget.h"

using namespace ModelView;
using ::testing::_;

class TestModelMapper : public ::testing::Test
{
public:
    ~TestModelMapper();
};

TestModelMapper::~TestModelMapper() = default;


TEST(TestModelMapper, onDataChange)
{
    EXPECT_EQ(1,1);
}
