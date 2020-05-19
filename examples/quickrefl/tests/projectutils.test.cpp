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
#include <mvvm/utils/fileutils.h>

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


    //! Creates project directory in the test directory and returns full path.
    //! Remove recursively previous one with the same name, if exist.
    //! FIXME remove duplication
    std::string create_project_dir(const std::string& name)
    {
        auto path = ModelView::Utils::join(testDir(), name);
        ModelView::Utils::remove_all(path);
        ModelView::Utils::create_directory(path);
        return path;
    }

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

TEST_F(ProjectUtilsTest, IsPossibleProjectDir)
{
    ApplicationModels models;
    auto project = ProjectUtils::CreateUntitledProject(&models);

    // empty directory can't be a project directory
    auto dirname = create_project_dir("test_IsPossibleProjectDir");
    EXPECT_FALSE(ProjectUtils::IsPossibleProjectDir(dirname));

    project->save(dirname);
    EXPECT_TRUE(ProjectUtils::IsPossibleProjectDir(dirname));
}
