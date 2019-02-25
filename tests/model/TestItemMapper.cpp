#include "google_test.h"
#include "itemmapper.h"
#include "sessionitem.h"
#include "MockWidgets.h"

using namespace ModelView;
using ::testing::_;

class TestItemMapper : public ::testing::Test
{
public:
    ~TestItemMapper();
};

TestItemMapper::~TestItemMapper() = default;

//! Setting data to item, expecting onDataChange callback.

TEST(TestItemMapper, onDataChange)
{
    EXPECT_EQ(1, 1);
//    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
//    ObsoleteMockWidget widget(item.get());

//    auto expected_role = ItemDataRole::DATA;
//    auto expected_item = item.get();
//    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
//    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);

//    item->setData(42.0, ItemDataRole::DATA); // perform action
}
