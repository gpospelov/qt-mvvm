// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <memory>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/itemcontroller.h>
#include <mvvm/signals/itemmapper.h>

using namespace ModelView;

//! Testing ItemController.

class ItemControllerTest : public ::testing::Test
{
public:
    class TestController : public ItemController<PropertyItem>
    {
    public:
        ~TestController();
        size_t ondata_change_call_count{0};
        size_t on_unsubscribe_call_count{0};
        void subscribe()
        {
            auto on_data_change = [this](SessionItem*, int) { ondata_change_call_count++; };
            currentItem()->mapper()->setOnDataChange(on_data_change, this);
        }

        void unsubscribe() { on_unsubscribe_call_count++; }
    };

    ~ItemControllerTest();
};

ItemControllerTest::~ItemControllerTest() = default;
ItemControllerTest::TestController::~TestController() = default;

//! Initial state.

TEST_F(ItemControllerTest, initialState)
{
    TestController controller;
    EXPECT_EQ(controller.currentItem(), nullptr);
}

//! Check that controller aware of item deletion.

TEST_F(ItemControllerTest, itemDeletedBeforeController)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();

    auto controller = std::make_unique<TestController>();
    controller->setItem(item);
    item->setData(42.0);

    EXPECT_EQ(controller->currentItem(), item);
    EXPECT_EQ(controller->ondata_change_call_count, 1);

    model.removeItem(model.rootItem(), "", 0);
    EXPECT_EQ(controller->currentItem(), nullptr);
}

//! Checks unsubscribe scenario.

TEST_F(ItemControllerTest, unsubscribeScenario)
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

TEST_F(ItemControllerTest, controllerDeletedBeforeItem)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();

    auto controller = std::make_unique<TestController>();
    controller->setItem(item);
    EXPECT_EQ(controller->currentItem(), item);

    controller.reset();
    item->setData(42.0);
}
