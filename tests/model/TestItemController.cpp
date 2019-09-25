#include "google_test.h"
#include "itemcontroller.h"
#include "itemmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "propertyitem.h"
#include <memory>

using namespace ModelView;

//! Testing ItemController.

class TestItemController : public ::testing::Test
{
public:
    class TestControllerV2 : public ItemControllerV2<PropertyItem>
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

TEST_F(TestItemController, initialStateV2)
{
    TestControllerV2 controller;
    EXPECT_EQ(controller.currentItem(), nullptr);
}

TEST_F(TestItemController, itemBeforeControllerV2)
{
    SessionModel model;
    auto item = dynamic_cast<PropertyItem*>(model.insertNewItem(Constants::PropertyType));

    std::unique_ptr<TestControllerV2> controller = std::make_unique<TestControllerV2>();
    controller->setItem(item);
    item->setData(42.0);

    EXPECT_EQ(controller->currentItem(), item);
    EXPECT_EQ(controller->ncount, 1);

    model.removeItem(model.rootItem(), "", 0);
    EXPECT_EQ(controller->currentItem(), nullptr);
}

TEST_F(TestItemController, controllerBeforeItemV2)
{
    SessionModel model;
    auto item = dynamic_cast<PropertyItem*>(model.insertNewItem(Constants::PropertyType));

    std::unique_ptr<TestControllerV2> controller = std::make_unique<TestControllerV2>();
    controller->setItem(item);
    EXPECT_EQ(controller->currentItem(), item);

    controller.reset();
    item->setData(42.0);
}
