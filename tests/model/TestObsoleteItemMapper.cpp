#include "google_test.h"
#include "obsoleteitemmapper.h"
#include "sessionitem.h"
#include "MockWidgets.h"

using namespace ModelView;
using ::testing::_;

class TestObsoleteItemMapper : public ::testing::Test
{
public:
    ~TestObsoleteItemMapper();
};

TestObsoleteItemMapper::~TestObsoleteItemMapper() = default;

//! Destroying item, expecting single call of onItemDestroy in MockWidget.

TEST(TestObsoleteItemMapper, onItemDestroy)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    ObsoleteMockWidget widget(item.get());

    auto expected_item = item.get();
    EXPECT_CALL(widget, onItemDestroy(expected_item)).Times(1);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);

    item.reset(); // perform action
}

//! Setting data to item, expecting onDataChange callback.

TEST(TestObsoleteItemMapper, onDataChange)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    ObsoleteMockWidget widget(item.get());

    auto expected_role = ItemDataRole::DATA;
    auto expected_item = item.get();
    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);

    item->setData(42.0, ItemDataRole::DATA); // perform action
}

//! Setting same data to item, expecting no callbacks on onDataChange.

TEST(TestObsoleteItemMapper, onDataChangeDuplicate)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    ObsoleteMockWidget widget(item.get());

    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(1);

    // perform actions, only one call should be triggered
    item->setData(42.0, ItemDataRole::DATA);
    item->setData(42.0, ItemDataRole::DATA); // same data
}

//! Setting mapper activity to false, change the data, expect no callbacks.

TEST(TestObsoleteItemMapper, setActivity)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    ObsoleteMockWidget widget(item.get());

    item->obsolete_mapper()->setActive(false);

    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);

    // perform actions, no calls should be triggered
    item->setData(42.0, ItemDataRole::DATA);
}

//! Unsubscribing from item, expecting no callbacks.


TEST(TestObsoleteItemMapper, unsubscribe)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    ObsoleteMockWidget widget1(item.get());
    ObsoleteMockWidget widget2(item.get());

    item->obsolete_mapper()->unsubscribe(&widget1);

    EXPECT_CALL(widget1, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget2, onDataChange(_, _)).Times(1);

    // perform action, only one widget should be triggered
    item->setData(42.0, ItemDataRole::DATA);
}
