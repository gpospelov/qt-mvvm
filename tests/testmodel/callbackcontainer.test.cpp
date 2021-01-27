// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/signals/callbackcontainer.h"

#include "google_test.h"
#include "mockwidgets.h"
#include "mvvm/model/sessionitem.h"
#include <memory>

using namespace ModelView;
using ::testing::_;

//! Testing CallbackContainer class.

class CallbackContainerTest : public ::testing::Test {
};

//! Callback container notifies single widget. Check if removal of widget disables notifications.

TEST_F(CallbackContainerTest, singleWidget)
{
    CallbackMockWidget widget;
    Signal<Callbacks::item_t> signal;

    signal.connect(std::bind(&CallbackMockWidget::onItemDestroy, &widget, std::placeholders::_1),
                   &widget);

    std::unique_ptr<SessionItem> item(new SessionItem);
    EXPECT_CALL(widget, onItemDestroy(item.get())).Times(1);

    // perform action
    signal(item.get());

    // removing client
    signal.remove_client(&widget);
    EXPECT_CALL(widget, onItemDestroy(_)).Times(0);

    // perform action
    signal(item.get());
}

//! Callback container notifies two widgets. Check if one widget is removed,
//! the second is still notified.

TEST_F(CallbackContainerTest, twoWidgets)
{
    CallbackMockWidget widget1, widget2;
    Signal<Callbacks::item_t> signal;

    signal.connect([&](SessionItem* item) { widget1.onItemDestroy(item); }, &widget1);

    signal.connect([&](SessionItem* item) { widget2.onItemDestroy(item); }, &widget2);

    std::unique_ptr<SessionItem> item(new SessionItem);
    EXPECT_CALL(widget1, onItemDestroy(item.get())).Times(1);
    EXPECT_CALL(widget2, onItemDestroy(item.get())).Times(1);

    // perform action
    signal(item.get());

    // removing one of client
    signal.remove_client(&widget1);
    EXPECT_CALL(widget1, onItemDestroy(_)).Times(0);
    EXPECT_CALL(widget2, onItemDestroy(item.get())).Times(1);

    // perform action
    signal(item.get());
}

//! Callback function with two parameters.

TEST_F(CallbackContainerTest, twoParameters)
{
    CallbackMockWidget widget1, widget2;
    Signal<Callbacks::item_int_t> signal;

    signal.connect([&](SessionItem* item, int role) { widget1.onDataChange(item, role); },
                   &widget1);

    signal.connect([&](SessionItem* item, int role) { widget2.onDataChange(item, role); },
                   &widget2);

    int expected_role = 42;
    std::unique_ptr<SessionItem> item(new SessionItem);
    EXPECT_CALL(widget1, onDataChange(item.get(), expected_role)).Times(1);
    EXPECT_CALL(widget2, onDataChange(item.get(), expected_role)).Times(1);

    // perform action
    signal(item.get(), expected_role);

    // removing one of client
    signal.remove_client(&widget1);
    EXPECT_CALL(widget1, onDataChange(_, _)).Times(0);
    EXPECT_CALL(widget2, onDataChange(item.get(), expected_role)).Times(1);

    // perform action
    signal(item.get(), expected_role);
}
