#include "google_test.h"
#include "callbackcontainer.h"
#include "model_types.h"
#include "sessionitem.h"
#include "MockWidgets.h"
#include <memory>

using namespace ModelView;

//! Testing CallbackContainer class.

class TestCallbackContainer : public ::testing::Test
{
public:
    ~TestCallbackContainer();
};

TestCallbackContainer::~TestCallbackContainer() = default;

TEST_F(TestCallbackContainer, initialState)
{
    CallbackMockWidget widget;
    CallbackContainer<Callbacks::item_t> container;

    container.add([&](SessionItem* item){
        widget.onItemDestroy(item);
    }, &widget);

    std::unique_ptr<SessionItem> item(new SessionItem);
    EXPECT_CALL(widget, onItemDestroy(item.get())).Times(1);

    // perform action
    container.notify(item.get());
}
