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
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>

//! Tests of ProjectUtils namespace functions.

class ProjectUtilsTest : public ::testing::Test
{
public:
    ~ProjectUtilsTest();

    class ApplicationModels : public ApplicationModelsInterface
    {
    public:
        std::unique_ptr<ModelView::SessionModel> sample_model;
        ApplicationModels() : sample_model(std::make_unique<ModelView::SessionModel>("SampleModel"))
        {
        }

        std::vector<ModelView::SessionModel*> persistent_models() const override
        {
            return {sample_model.get()};
        };
    };

    static inline const std::string test_subdir = "test_ProjectUtilsTest";
    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_subdir); }
    std::string testDir() const { return TestUtils::TestDirectoryPath(test_subdir); }
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

TEST_F(ProjectUtilsTest, ProjectWindowTitle)
{
    ApplicationModels models;
    auto project = ProjectUtils::CreateUntitledProject(&models);

    // unmodified project without projectDir
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), "Untitled");

    models.sample_model->insertItem<ModelView::PropertyItem>();
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), "*Untitled");

    // saving in a project directory
    project->save(testDir());
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), test_subdir);

    // modifying
    models.sample_model->insertItem<ModelView::PropertyItem>();
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), "*" + test_subdir);
}
