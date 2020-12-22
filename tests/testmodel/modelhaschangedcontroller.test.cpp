// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/project/modelhaschangedcontroller.h"

#include "google_test.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionmodel.h"

using namespace ModelView;

//! Tests for ModelHasChangedController class.

class ModelHasChangedControllerTest : public ::testing::Test {
};

//! Tests initial state of the controller.

TEST_F(ModelHasChangedControllerTest, initialState)
{
    SessionModel model;
    ModelHasChangedController controller(&model);
    EXPECT_FALSE(controller.hasChanged());
}

//! Tests if controller 'sees' item insertion.

TEST_F(ModelHasChangedControllerTest, insertItem)
{
    SessionModel model;
    ModelHasChangedController controller(&model);

    model.insertItem<PropertyItem>();
    EXPECT_TRUE(controller.hasChanged());

    controller.resetChanged();
    EXPECT_FALSE(controller.hasChanged());
}

//! Tests if controller sees item insertion.

TEST_F(ModelHasChangedControllerTest, removeItem)
{
    SessionModel model;
    model.insertItem<PropertyItem>();

    ModelHasChangedController controller(&model);
    EXPECT_FALSE(controller.hasChanged());

    model.removeItem(model.rootItem(), {"", 0});

    EXPECT_TRUE(controller.hasChanged());
}

//! Tests if controller sees item data change.

TEST_F(ModelHasChangedControllerTest, dataChanged)
{
    SessionModel model;
    auto item = model.insertItem<PropertyItem>();

    ModelHasChangedController controller(&model);
    EXPECT_FALSE(controller.hasChanged());

    item->setData(42.0);
    EXPECT_TRUE(controller.hasChanged());
}

//! Tests if controller sees model reset.

TEST_F(ModelHasChangedControllerTest, modelReset)
{
    SessionModel model;
    model.insertItem<PropertyItem>();

    ModelHasChangedController controller(&model);
    EXPECT_FALSE(controller.hasChanged());

    model.clear();
    EXPECT_TRUE(controller.hasChanged());
}

//! Tests callback functioning.

TEST_F(ModelHasChangedControllerTest, callback)
{
    int change_count{0};
    auto on_change = [&change_count]() { change_count++; };

    SessionModel model;
    ModelHasChangedController controller(&model, on_change);

    model.insertItem<PropertyItem>();
    EXPECT_TRUE(controller.hasChanged());
    EXPECT_EQ(change_count, 1);

    controller.resetChanged();
    EXPECT_FALSE(controller.hasChanged());
    EXPECT_EQ(change_count, 1);
}

//! Tests callback functioning.

TEST_F(ModelHasChangedControllerTest, timeOfLife)
{
    int change_count{0};
    auto on_change = [&change_count]() { change_count++; };

    SessionModel model;
    auto controller = std::make_unique<ModelHasChangedController>(&model, on_change);

    // change the model, check controller
    model.insertItem<PropertyItem>();
    EXPECT_TRUE(controller->hasChanged());
    EXPECT_EQ(change_count, 1);

    // remove controller, change the model
    controller.reset();
    model.insertItem<PropertyItem>();
    EXPECT_EQ(change_count, 1);
}
