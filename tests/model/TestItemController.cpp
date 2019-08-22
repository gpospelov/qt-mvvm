#include "google_test.h"
#include "itemcontroller.h"
#include "itemmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <memory>

using namespace ModelView;

//! Testing ItemController.

class TestItemController : public ::testing::Test
{
public:
    class TestController : public ItemController
    {
    public:
        int ncount{0};
        void subscribe()
        {
            auto on_data_change = [this](SessionItem*, int) { ncount++; };
            currentItem()->mapper()->setOnDataChange(on_data_change, this);
        }
    };
    ~TestItemController();
};

TestItemController::~TestItemController() = default;

//! Initial state.

TEST_F(TestItemController, initialState)
{
    ItemController controller;
    EXPECT_EQ(controller.currentItem(), nullptr);
}

TEST_F(TestItemController, itemBeforeController)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::BaseType);

    std::unique_ptr<TestController> controller = std::make_unique<TestController>();
    controller->setItem(item);
    item->setData(42.0);

    EXPECT_EQ(controller->currentItem(), item);
    EXPECT_EQ(controller->ncount, 1);

    model.removeItem(model.rootItem(), "", 0);
    EXPECT_EQ(controller->currentItem(), nullptr);
}

TEST_F(TestItemController, controllerBeforeItem)
{
    SessionModel model;
    auto item = model.insertNewItem(Constants::BaseType);

    std::unique_ptr<TestController> controller = std::make_unique<TestController>();
    controller->setItem(item);
    EXPECT_EQ(controller->currentItem(), item);

    controller.reset();
    item->setData(42.0);
}
