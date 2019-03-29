#include "MockWidgets.h"
#include "compounditem.h"
#include "google_test.h"
#include "itemmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"

using namespace ModelView;
using ::testing::_;

class TestItemMapper : public ::testing::Test
{
public:
    ~TestItemMapper();
};

TestItemMapper::~TestItemMapper() = default;

//! Check that mapper works only in model context.

TEST(TestItemMapper, initialState)
{
    // item outside model context can't have a mapper
    std::unique_ptr<SessionItem> item = std::make_unique<SessionItem>();
    EXPECT_THROW(item->mapper(), std::runtime_error);

    // item in model context does have a mapper
    SessionModel model;
    auto item2 = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);
    EXPECT_NO_THROW(item2->mapper());
}

//! Destroying item, expecting single call of onItemDestroy in MockWidget.
// FIXME Provide onItemDestroy or cleanup

TEST(TestItemMapper, onItemDestroy)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);

    MockWidgetForItem widget(item);

    auto expected_item = item;
    EXPECT_CALL(widget, onItemDestroy(expected_item)).Times(1);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);

    // performing action
    model.removeItem(model.rootItem(), "",  0);
}

//! Setting data to item, expecting onDataChange callback.

TEST(TestItemMapper, onDataChange)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);

    MockWidgetForItem widget(item);

    auto expected_role = ItemDataRole::DATA;
    auto expected_item = item;
    EXPECT_CALL(widget, onDataChange(expected_item, expected_role)).Times(1);

    // perform action
    item->setData(42.0, ItemDataRole::DATA);
}

//! Setting same data to item, expecting no callbacks on onDataChange.

TEST(TestItemMapper, onDataChangeDuplicate)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);

    MockWidgetForItem widget(item);

    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(1);

    // perform actions, only one call should be triggered
    item->setData(42.0, ItemDataRole::DATA);
    item->setData(42.0, ItemDataRole::DATA); // same data
}

//! Setting mapper activity to false, change the data, expect no callbacks.

TEST(TestItemMapper, setActivity)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);

    MockWidgetForItem widget(item);

    item->mapper()->setActive(false);

    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);

    // perform actions, no calls should be triggered
    item->setData(42.0, ItemDataRole::DATA);
}

//! Unsubscribing from item, expecting no callbacks.

TEST(TestItemMapper, unsubscribe)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::BaseType, model.rootItem(), "", 0);

    MockWidgetForItem widget1(item);
    MockWidgetForItem widget2(item);

    item->mapper()->unsubscribe(&widget1);

    EXPECT_CALL(widget1, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget2, onDataChange(_, _)).Times(1);

    // perform action, only one widget should be triggered
    item->setData(42.0, ItemDataRole::DATA);
}

//! Changing item property.

TEST(TestItemMapper, onPropertyChange)
{
    SessionModel model;
    auto item = dynamic_cast<CompoundItem*>(model.insertNewItem(Constants::CompoundType));
    EXPECT_TRUE(item != nullptr);

    auto property = item->addProperty<PropertyItem>("height", 42.0);

    MockWidgetForItem widget(item);

    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget, onPropertyChange(item, "height")).Times(1);

    // perform action
    item->setItemValue("height", 43.0);
    EXPECT_EQ(item->getItemValue("height"), 43.0);
    EXPECT_EQ(property->data(ItemDataRole::DATA).toDouble(), 43.0);
}
