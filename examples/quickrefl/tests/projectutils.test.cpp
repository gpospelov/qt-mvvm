// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "applicationmodelsinterface.h"
#include "google_test.h"
#include "projectinterface.h"
#include "projectutils.h"
#include "test_utils.h"
#include <mvvm/model/sessionmodel.h>

//! Tests of ProjectUtils namespace functions.

class ProjectUtilsTest : public ::testing::Test
{
public:
    ~ProjectUtilsTest();

    class ApplicationModels : public ApplicationModelsInterface
    {
    public:
        std::vector<ModelView::SessionModel*> persistent_models() const override { return {}; };
    };
};

ProjectUtilsTest::~ProjectUtilsTest() = default;

//! Testing helper structure.

TEST_F(ProjectUtilsTest, SuggestFileName)
{
    ModelView::SessionModel model("TestModel");
    EXPECT_EQ(std::string("testmodel.json"), ProjectUtils::SuggestFileName(model));
}

TEST_F(ProjectUtilsTest, CreateUntitledProject)
{
    ApplicationModels models;
    auto project = ProjectUtils::CreateUntitledProject(&models);
    EXPECT_TRUE(project->projectDir().empty());
}
