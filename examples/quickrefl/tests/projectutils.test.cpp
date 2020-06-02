// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "applicationmodelsinterface.h"
#include "folderbasedtest.h"
#include "google_test.h"
#include <mvvm/interfaces/projectinterface.h>
#include "projectutils.h"
#include "test_utils.h"
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/utils/fileutils.h>

//! Tests of ProjectUtils namespace functions.

class ProjectUtilsTest : public FolderBasedTest
{
public:
    ProjectUtilsTest() : FolderBasedTest("test_ProjectUtils") {}
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
    project->save(testPath());
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), testDir());

    // modifying
    models.sample_model->insertItem<ModelView::PropertyItem>();
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), "*" + testDir());
}

TEST_F(ProjectUtilsTest, IsPossibleProjectDir)
{
    ApplicationModels models;
    auto project = ProjectUtils::CreateUntitledProject(&models);

    // empty directory can't be a project directory
    auto dirname = createEmptyDir("test_IsPossibleProjectDir");
    EXPECT_FALSE(ProjectUtils::IsPossibleProjectDir(dirname));

    project->save(dirname);
    EXPECT_TRUE(ProjectUtils::IsPossibleProjectDir(dirname));
}
