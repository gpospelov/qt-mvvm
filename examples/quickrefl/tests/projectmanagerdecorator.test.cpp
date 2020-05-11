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
#include "projectmanagerdecorator.h"
#include "test_utils.h"
#include <cctype>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/utils/fileutils.h>

namespace
{
const std::string samplemodel_name = "samplemodel";

} // namespace

//! Tests for ProjectManager class.

class ProjectManagerDecoratorTest : public ::testing::Test
{
public:
    ~ProjectManagerDecoratorTest();

    class ApplicationModels : public ApplicationModelsInterface
    {
    public:
        std::unique_ptr<ModelView::SessionModel> sample_model;
        ApplicationModels()
            : sample_model(std::make_unique<ModelView::SessionModel>(samplemodel_name))
        {
        }

        std::vector<ModelView::SessionModel*> persistent_models() const override
        {
            return {sample_model.get()};
        };
    };

    static inline std::string test_dir = "not-yet-defined";
    static inline const std::string test_subdir = "test_QuickReflProjectManager";
    static void SetUpTestCase() { test_dir = TestUtils::CreateTestDirectory(test_subdir); }
    std::string testDir() const { return test_dir; }

    //! Creates project directory in the test directory and returns full path.
    //! Remove recursively previous one with the same name, if exist.
    std::string create_project_dir(const std::string& name)
    {
        auto path = ModelView::Utils::join(testDir(), name);
        ModelView::Utils::remove_all(path);
        ModelView::Utils::create_directory(path);
        return path;
    }
};

ProjectManagerDecoratorTest::~ProjectManagerDecoratorTest() = default;

//! Initial state of ProjectManager. Project created, and not-saved.

TEST_F(ProjectManagerDecoratorTest, initialState)
{
    auto open_dir = []() -> std::string { return {}; };
    auto create_dir = []() -> std::string { return {}; };

    ApplicationModels models;
    ProjectManagerDecorator manager(&models, open_dir, create_dir);
    EXPECT_TRUE(manager.currentProjectDir().empty());
}

//! Starting from new document (without project dir defined).
//! Create new project in given directory.

// TEST_F(ProjectManagerDecoratorTest, untitledEmptyCreateNew)
//{
//    auto project_dir = create_project_dir("Project_untitledEmptyCreateNew");

//    auto open_dir = []() -> std::string { return {}; };
//    auto create_dir = [&project_dir]() -> std::string { return project_dir; };

//    ApplicationModels models;
//    ProjectManager manager(&models, open_dir, create_dir);
//    EXPECT_TRUE(manager.currentProjectDir().empty());

//    // saving new project to 'project_dir' directory.
//    EXPECT_TRUE(manager.createNewProject());

//    // checking that current projectDir has pointing to the right place
//    EXPECT_EQ(manager.currentProjectDir(), project_dir);

//    // project directory should contain a json file with the model
//    auto model_json = ModelView::Utils::join(project_dir, samplemodel_name + ".json");
//    EXPECT_TRUE(ModelView::Utils::exists(model_json));
//}

//! Starting from new document (without project dir defined).
//! Saving project. Same behavior as SaveAs.

TEST_F(ProjectManagerDecoratorTest, untitledEmptySaveCurrentProject)
{
    auto project_dir = create_project_dir("Project_untitledEmptySaveCurrentProject");

    auto open_dir = []() -> std::string { return {}; };
    auto create_dir = [&project_dir]() -> std::string { return project_dir; };

    ApplicationModels models;
    ProjectManagerDecorator manager(&models, open_dir, create_dir);
    EXPECT_TRUE(manager.currentProjectDir().empty());

    // saving new project to 'project_dir' directory.
    EXPECT_TRUE(manager.saveCurrentProject());

    // checking thaxt current projectDir has pointing to the right place
    EXPECT_EQ(manager.currentProjectDir(), project_dir);

    // project directory should contain a json file with the model
    auto model_json = ModelView::Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(ModelView::Utils::exists(model_json));
}

//! Starting from new document (without project dir defined).
//! Save under given name.

TEST_F(ProjectManagerDecoratorTest, untitledEmptySaveAs)
{
    auto project_dir = create_project_dir("Project_untitledEmptySaveAs");

    auto open_dir = []() -> std::string { return {}; };
    auto create_dir = [&project_dir]() -> std::string { return project_dir; };

    ApplicationModels models;
    ProjectManagerDecorator manager(&models, open_dir, create_dir);
    EXPECT_TRUE(manager.currentProjectDir().empty());

    // saving new project to "project_dir" directory.
    EXPECT_TRUE(manager.saveProjectAs());

    // checking that current projectDir has pointing to the right place
    EXPECT_EQ(manager.currentProjectDir(), project_dir);

    // project directory should contain a json file with the model
    auto model_json = ModelView::Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(ModelView::Utils::exists(model_json));
}

//! Starting from new document (without project dir defined).
//! Attempt to save under empty name, immitating the user canceled directory selection dialog.

TEST_F(ProjectManagerDecoratorTest, untitledEmptySaveAsCancel)
{
    auto open_dir = []() -> std::string { return {}; };
    auto create_dir = []() -> std::string { return {}; }; // empty name imitates canceling

    ApplicationModels models;
    ProjectManagerDecorator manager(&models, open_dir, create_dir);
    EXPECT_TRUE(manager.currentProjectDir().empty());

    // saving new project to "project_dir" directory.
    EXPECT_FALSE(manager.saveProjectAs());
    EXPECT_TRUE(manager.currentProjectDir().empty());
}

//! Starting from new document (without project dir defined).
//! Attempt to save in the non-existing directory.

TEST_F(ProjectManagerDecoratorTest, untitledEmptySaveAsWrongDir)
{
    auto open_dir = []() -> std::string { return {}; };
    auto create_dir = []() -> std::string { return "non-existing"; }; // empty name imitates canceling

    ApplicationModels models;
    ProjectManagerDecorator manager(&models, open_dir, create_dir);

    // saving new project to "project_dir" directory.
    EXPECT_FALSE(manager.saveProjectAs());
    EXPECT_TRUE(manager.currentProjectDir().empty());
}
