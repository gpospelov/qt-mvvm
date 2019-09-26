#include "google_test.h"
#include "itemcontroller.h"
#include "itemmapper.h"
#include "propertyitem.h"
#include "sessionmodel.h"
#include <memory>

using namespace ModelView;

//! Testing ItemController.

class TestItemController : public ::testing::Test
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

        void unsubscribe()
        {
            on_unsubscribe_call_count++;
        }

    };

    ~TestItemController();
};

TestItemController::~TestItemController() = default;
TestItemController::TestController::~TestController() = default;

//! Initial state.

TEST_F(TestItemController, initialState)
{
    TestController controller;
    EXPECT_EQ(controller.currentItem(), nullptr);
}

//! Check that controller aware of item deletion.

TEST_F(TestItemController, itemDeletedBeforeController)
{
    SessionModel model;
    auto item = dynamic_cast<PropertyItem*>(model.insertNewItem(Constants::PropertyType));

    auto controller = std::make_unique<TestController>();
    controller->setItem(item);
    item->setData(42.0);

    EXPECT_EQ(controller->currentItem(), item);
    EXPECT_EQ(controller->ondata_change_call_count, 1);

    model.removeItem(model.rootItem(), "", 0);
    EXPECT_EQ(controller->currentItem(), nullptr);
}

//! Checks unsubscribe scenario.

TEST_F(TestItemController, unsubscribeScenario)
{
    SessionModel model;
    auto item = dynamic_cast<PropertyItem*>(model.insertNewItem(Constants::PropertyType));

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

TEST_F(TestItemController, controllerDeletedBeforeItem)
{
    SessionModel model;
    auto item = dynamic_cast<PropertyItem*>(model.insertNewItem(Constants::PropertyType));

    auto controller = std::make_unique<TestController>();
    controller->setItem(item);
    EXPECT_EQ(controller->currentItem(), item);

    controller.reset();
    item->setData(42.0);
}

