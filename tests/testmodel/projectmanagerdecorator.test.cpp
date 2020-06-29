// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "google_test.h"
#include <cctype>
#include <mvvm/interfaces/applicationmodelsinterface.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/project/project_types.h>
#include <mvvm/project/projectmanagerdecorator.h>
#include <mvvm/utils/fileutils.h>

using namespace ModelView;

namespace
{
const std::string samplemodel_name = "samplemodel";

} // namespace

//! Tests for ProjectManager class.

class ProjectManagerDecoratorTest : public FolderBasedTest
{
public:
    ProjectManagerDecoratorTest() : FolderBasedTest("test_ProjectManagerDecorator") {}
    ~ProjectManagerDecoratorTest();

    class ApplicationModels : public ApplicationModelsInterface
    {
    public:
        std::unique_ptr<SessionModel> sample_model;
        ApplicationModels() : sample_model(std::make_unique<SessionModel>(samplemodel_name)) {}

        std::vector<SessionModel*> persistent_models() const override
        {
            return {sample_model.get()};
        };
    };
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

TEST_F(ProjectManagerDecoratorTest, untitledEmptyCreateNew)
{
    const auto project_dir = createEmptyDir("Project_untitledEmptyCreateNew");

    auto open_dir = []() -> std::string { return {}; };
    auto create_dir = [&project_dir]() -> std::string { return project_dir; };

    ApplicationModels models;
    ProjectManagerDecorator manager(&models, open_dir, create_dir);
    EXPECT_TRUE(manager.currentProjectDir().empty());

    // saving new project to 'project_dir' directory.
    EXPECT_TRUE(manager.createNewProject());

    // checking that current projectDir has pointing to the right place
    EXPECT_EQ(manager.currentProjectDir(), project_dir);

    // project directory should contain a json file with the model
    auto model_json = Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));
}

//! Starting from new document (without project dir defined).
//! Saving project. Same behavior as SaveAs.

TEST_F(ProjectManagerDecoratorTest, untitledEmptySaveCurrentProject)
{
    const auto project_dir = createEmptyDir("Project_untitledEmptySaveCurrentProject");

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
    auto model_json = Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));
}

//! Starting from new document (without project dir defined).
//! Save under given name.

TEST_F(ProjectManagerDecoratorTest, untitledEmptySaveAs)
{
    const auto project_dir = createEmptyDir("Project_untitledEmptySaveAs");

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
    auto model_json = Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));
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
    auto create_dir = []() -> std::string {
        return "non-existing";
    }; // empty name imitates canceling

    ApplicationModels models;
    ProjectManagerDecorator manager(&models, open_dir, create_dir);

    // saving new project to "project_dir" directory.
    EXPECT_FALSE(manager.saveProjectAs());
    EXPECT_TRUE(manager.currentProjectDir().empty());
}

//! Untitled, modified document. Attempt to open existing project will lead to
//! the dialog save/discard/cancel. As a result of whole exersize, existing project
//! should be opened, previous project saved.

TEST_F(ProjectManagerDecoratorTest, untitledModifiedOpenExisting)
{
    ApplicationModels models;
    const auto existing_project_dir = createEmptyDir("Project_untitledModifiedOpenExisting1");
    const auto unsaved_project_dir = createEmptyDir("Project_untitledModifiedOpenExisting2");

    // create "existing project"
    {
        auto open_dir = []() -> std::string { return {}; };
        auto create_dir = [&existing_project_dir]() -> std::string { return existing_project_dir; };

        ProjectManagerDecorator manager(&models, open_dir, create_dir);
        manager.saveProjectAs();
    }

    // preparing manager with untitled, unmodified project
    auto open_dir = [&existing_project_dir]() -> std::string { return existing_project_dir; };
    auto create_dir = [&unsaved_project_dir]() -> std::string { return unsaved_project_dir; };
    auto result = SaveChangesAnswer::DISCARD;
    auto ask_create = [&result]() {
        result = SaveChangesAnswer::SAVE;
        return SaveChangesAnswer::SAVE;
    };
    ProjectManagerDecorator manager(&models, open_dir, create_dir);
    manager.setSaveChangesAnswerCallback(ask_create);

    // modifying untitled project
    models.sample_model->insertItem<PropertyItem>();
    EXPECT_TRUE(manager.isModified());
    EXPECT_TRUE(manager.currentProjectDir().empty());

    // attempt to open existing project
    manager.openExistingProject();

    // check if user was asked and his answer coincide with expectation
    EXPECT_EQ(result, SaveChangesAnswer::SAVE);

    // check that previous project was saved
    auto model_json = Utils::join(unsaved_project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));

    // currently manager is pointing to existing project
    EXPECT_FALSE(manager.isModified());
    EXPECT_EQ(manager.currentProjectDir(), existing_project_dir);
}
