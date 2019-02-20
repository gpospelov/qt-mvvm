#include "google_test.h"
#include "callbackcontainer.h"
#include "model_types.h"
#include "sessionitem.h"
#include "MockWidgets.h"
#include <memory>

using namespace ModelView;
using ::testing::_;

//! Testing CallbackContainer class.

class TestCallbackContainer : public ::testing::Test
{
public:
    ~TestCallbackContainer();
};

TestCallbackContainer::~TestCallbackContainer() = default;

//! Callback container notifies single widget. Check if removal of widget disables notifications.

TEST_F(TestCallbackContainer, singleWidget)
{
    CallbackMockWidget widget;
    CallbackContainer<Callbacks::item_t> container;

    container.add(std::bind(&CallbackMockWidget::onItemDestroy, &widget, std::placeholders::_1),
                  &widget);

    std::unique_ptr<SessionItem> item(new SessionItem);
    EXPECT_CALL(widget, onItemDestroy(item.get())).Times(1);

    // perform action
    container.notify(item.get());

    // removing client
    container.remove_client(&widget);
    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);

    // perform action
    container.notify(item.get());
}

//! Callback container notifies two widgets. Check if one widget is removed,
//! the second is still notified.

TEST_F(TestCallbackContainer, twoWidgets)
{
    CallbackMockWidget widget1, widget2;
    CallbackContainer<Callbacks::item_t> container;

    container.add([&](SessionItem* item){
        widget1.onItemDestroy(item);
    }, &widget1);

    container.add([&](SessionItem* item){
        widget2.onItemDestroy(item);
    }, &widget2);

    std::unique_ptr<SessionItem> item(new SessionItem);
    EXPECT_CALL(widget1, onItemDestroy(item.get())).Times(1);
    EXPECT_CALL(widget2, onItemDestroy(item.get())).Times(1);

    // perform action
    container.notify(item.get());

    // removing one of client
    container.remove_client(&widget1);
    EXPECT_CALL(widget1, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget2, onItemDestroy(item.get())).Times(1);

    // perform action
    container.notify(item.get());
}

//! Callback function with two parameters.

TEST_F(TestCallbackContainer, twoParameters)
{
    CallbackMockWidget widget1, widget2;
    CallbackContainer<Callbacks::item_int_t> container;

    container.add([&](SessionItem* item, int role){
        widget1.onDataChange(item, role);
    }, &widget1);

    container.add([&](SessionItem* item, int role){
        widget2.onDataChange(item, role);
    }, &widget2);

    int expected_role = 42;
    std::unique_ptr<SessionItem> item(new SessionItem);
    EXPECT_CALL(widget1, onDataChange(item.get(), expected_role)).Times(1);
    EXPECT_CALL(widget2, onDataChange(item.get(), expected_role)).Times(1);

    // perform action
    container.notify(item.get(), expected_role);

    // removing one of client
    container.remove_client(&widget1);
    EXPECT_CALL(widget1, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget2, onDataChange(item.get(), expected_role)).Times(1);

    // perform action
    container.notify(item.get(), expected_role);
}
