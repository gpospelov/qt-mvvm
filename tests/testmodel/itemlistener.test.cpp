// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/signals/itemlistener.h"

#include "google_test.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionmodel.h"
#include <memory>

using namespace ModelView;

//! Testing ItemListener.

class ItemListenerTest : public ::testing::Test {
public:
    class TestController : public ItemListener<PropertyItem> {
    public:
        size_t ondata_change_call_count{0};
        size_t on_unsubscribe_call_count{0};
        void subscribe()
        {
            auto on_data_change = [this](SessionItem*, int) { ondata_change_call_count++; };
            setOnDataChange(on_data_change);
        }

        void unsubscribe() { on_unsubscribe_call_count++; }
    };
};

//! Initial state.

TEST_F(ItemListenerTest, initialState)
{
    TestController controller;
    EXPECT_EQ(controller.currentItem(), nullptr);
}

//! Check that controller aware of item deletion.

TEST_F(ItemListenerTest, itemDeletedBeforeController)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();

    auto controller = std::make_unique<TestController>();
    controller->setItem(item);
    item->setData(42.0);

    EXPECT_EQ(controller->currentItem(), item);
    EXPECT_EQ(controller->ondata_change_call_count, 1);

    model.removeItem(model.rootItem(), {"", 0});
    EXPECT_EQ(controller->currentItem(), nullptr);
}

//! Checks unsubscribe scenario.

TEST_F(ItemListenerTest, unsubscribeScenario)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();

    auto controller = std::make_unique<TestController>();
    controller->setItem(item);
    item->setData(42.0);

    EXPECT_EQ(controller->currentItem(), item);
    EXPECT_EQ(controller->ondata_change_call_count, 1);
    EXPECT_EQ(controller->on_unsubscribe_call_count, 0);

    // setting item to nullptr
    controller->setItem(nullptr);
    EXPECT_EQ(controller->currentItem(), nullptr);
    EXPECT_EQ(controller->on_unsubscribe_call_count, 1);
    // change in data shouldn't lead to update
    item->setData(45.0);
    EXPECT_EQ(controller->ondata_change_call_count, 1);
}

//! Checks that controller can be deleted before item.

TEST_F(ItemListenerTest, controllerDeletedBeforeItem)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();

    auto controller = std::make_unique<TestController>();
    controller->setItem(item);
    EXPECT_EQ(controller->currentItem(), item);

    controller.reset();
    item->setData(42.0);
}
