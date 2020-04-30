// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "projectchangecontroller.h"
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>

using namespace ModelView;

//! Tests for ProjectChangeController class.

class ProjectChangeControllerTest : public ::testing::Test
{
public:
    ~ProjectChangeControllerTest();
};

ProjectChangeControllerTest::~ProjectChangeControllerTest() = default;

TEST_F(ProjectChangeControllerTest, initialState)
{
    SessionModel sample_model("SampleModel");
    SessionModel material_model("MaterialModel");
    std::vector<SessionModel*> models = {&sample_model, &material_model};

    ProjectChangedController controller(models);
    EXPECT_FALSE(controller.hasChanged());
}

TEST_F(ProjectChangeControllerTest, twoModelsChange)
{
    SessionModel sample_model("SampleModel");
    SessionModel material_model("MaterialModel");
    std::vector<SessionModel*> models = {&sample_model, &material_model};

    ProjectChangedController controller(models);

    sample_model.insertItem<PropertyItem>();
    material_model.insertItem<PropertyItem>();

    EXPECT_TRUE(controller.hasChanged());

    controller.resetChanged();
    EXPECT_FALSE(controller.hasChanged());
}
