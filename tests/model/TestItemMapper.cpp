#include "google_test.h"
#include "itemmapper.h"
#include "sessionitem.h"
#include "ItemMockWidget.h"

using namespace ModelView;
using ::testing::_;

class TestItemMapper : public ::testing::Test
{
public:
    ~TestItemMapper();
};

TestItemMapper::~TestItemMapper() = default;

//! Destroying item, expecting single call of onItemDestroy in MockWidget.

TEST(TestItemMapper, onItemDestroy)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    MockWidget widget(item.get());

    auto expected_item = item.get();
    EXPECT_CALL(widget, onItemDestroy(expected_item)).Times(1);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);

    item.reset(); // perform action
}

//! Setting data to item, expecting onDataChange callback.

TEST(TestItemMapper, onDataChange)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    MockWidget widget(item.get());

    auto expected_role = ItemDataRole::DATA;
    auto expected_item = item.get();
    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);

    item->setData(42.0, ItemDataRole::DATA); // perform action
}

//! Setting same data to item, expecting no callbacks on onDataChange.

TEST(TestItemMapper, onDataChangeDuplicate)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    MockWidget widget(item.get());

    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(1);

    // perform actions, only one call should be triggered
    item->setData(42.0, ItemDataRole::DATA);
    item->setData(42.0, ItemDataRole::DATA); // same data
}

//! Setting mapper activity to false, change the data, expect no callbacks.

TEST(TestItemMapper, setActivity)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    MockWidget widget(item.get());

    item->mapper()->setActive(false);

    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);

    // perform actions, no calls should be triggered
    item->setData(42.0, ItemDataRole::DATA);
}

//! Unsubscribing from item, expecting no callbacks.


TEST(TestItemMapper, unsubscribe)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    MockWidget widget1(item.get());
    MockWidget widget2(item.get());

    item->mapper()->unsubscribe(&widget1);

    EXPECT_CALL(widget1, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget2, onDataChange(_, _)).Times(1);

    // perform action, only one widget should be triggered
    item->setData(42.0, ItemDataRole::DATA);
}
