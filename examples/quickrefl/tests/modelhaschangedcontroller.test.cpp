// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "modelhaschangedcontroller.h"
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>

using namespace ModelView;

//! Tests for ModelHasChangedController class.

class ModelHasChangedControllerTest : public ::testing::Test
{
public:
    ~ModelHasChangedControllerTest();
};

ModelHasChangedControllerTest::~ModelHasChangedControllerTest() = default;

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
