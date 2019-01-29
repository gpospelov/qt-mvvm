#include "google_test.h"
#include "itemmapper.h"
#include "sessionitem.h"
#include "ItemTestWidget.h"

using namespace ModelView;
using ::testing::_;

class TestItemMapper : public ::testing::Test
{
public:
    ~TestItemMapper();
};

TestItemMapper::~TestItemMapper() = default;

class MockWidget : public TestUtils::ItemTestWidgetInterface {
public:
    MockWidget(SessionItem* item) {
        TestUtils::ConnectItemWidget(this, item);
    }
    ~MockWidget();
    MOCK_METHOD1(onItemDestroy, void(SessionItem* item));
    MOCK_METHOD2(onDataChange, void(SessionItem* item, int role));
};

MockWidget::~MockWidget() = default;

//! Destroying item, expecting single onItemDestroy.

TEST_F(TestItemMapper, onItemDestroy)
{
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    MockWidget widget(item.get());

    auto expected_item = item.get();
    EXPECT_CALL(widget, onItemDestroy(expected_item)).Times(1);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);

    item.reset(); // perform action
}

//! Setting data to item, expecting onDataChange callback.

//TEST_F(TestItemMapper, onDataChange)
//{
//    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
//    MockWidget widget(item.get());

//    auto expected_role = ItemDataRole::DATA;
//    auto expected_item = item.get();
//    EXPECT_CALL(widget, onItemDestroy(expected_item)).Times(0);
//    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);

//    item->setData(42.0, ItemDataRole::DATA); // perform action
//}
