#include "google_test.h"
#include "test_utils.h"
#include "compounditem.h"
#include <memory>

using namespace ModelView;

//! Test of CompountItem machinery (property children etc).

class TestCompoundItem : public ::testing::Test
{
public:
    ~TestCompoundItem();
};

TestCompoundItem::~TestCompoundItem() = default;

TEST_F(TestCompoundItem, addProperty)
{
    CompoundItem item;
//    item.addProperty("width", 42.0);
}
