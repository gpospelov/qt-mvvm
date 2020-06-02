// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/interfaces/applicationmodelsinterface.h>
#include "folderbasedtest.h"
#include "google_test.h"
#include "projectmanager.h"
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

class ProjectManagerTest : public FolderBasedTest
{
public:
    ProjectManagerTest() : FolderBasedTest("test_ProjectManager") {}
    ~ProjectManagerTest();

    class ApplicationModels : public ModelView::ApplicationModelsInterface
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
};

ProjectManagerTest::~ProjectManagerTest() = default;

//! Initial state of ProjectManager. Project created, and not-saved.

TEST_F(ProjectManagerTest, initialState)
{
    ApplicationModels models;
    ProjectManager manager(&models);
    EXPECT_TRUE(manager.currentProjectDir().empty());
    EXPECT_FALSE(manager.isModified());
}

// ----------------------------------------------------------------------------
// Untitled, empty project
// ----------------------------------------------------------------------------

//! Creating new project. Use untitled+empty project as a starting point.
//! Should succeed, since old empty project doesn't need to be saved.

TEST_F(ProjectManagerTest, untitledEmptyNew)
{
    ApplicationModels models;
    ProjectManager manager(&models);

    const auto project_dir = createEmptyDir("Project_untitledEmptyNew");
    EXPECT_TRUE(manager.createNewProject(project_dir));

    EXPECT_EQ(manager.currentProjectDir(), project_dir);
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = ModelView::Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(ModelView::Utils::exists(model_json));
}

//! Saving of new project. Use untitled+empty project as a starting point.
//! Should fail since project directory is not defined.

TEST_F(ProjectManagerTest, untitledEmptySave)
{
    ApplicationModels models;
    ProjectManager manager(&models);
    EXPECT_FALSE(manager.saveCurrentProject());
    EXPECT_FALSE(manager.isModified());
}

//! Saving of new project. Use untitled+empty project as a starting point.
//! Should be saved, file sould appear on disk.

TEST_F(ProjectManagerTest, untitledEmptySaveAs)
{
    ApplicationModels models;
    ProjectManager manager(&models);

    const auto project_dir = createEmptyDir("Project_untitledEmptySaveAs");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = ModelView::Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(ModelView::Utils::exists(model_json));
}

// ----------------------------------------------------------------------------
// Untitled, modified
// ----------------------------------------------------------------------------

//! Creating new project. Use untitled+modified project as a starting point.
//! Should fail, since modified old project will prevent creation of the new one.

TEST_F(ProjectManagerTest, untitledModifiedNew)
{
    ApplicationModels models;
    ProjectManager manager(&models);

    // modifying the model
    models.sample_model->insertItem<ModelView::PropertyItem>();

    EXPECT_TRUE(manager.isModified());

    const auto project_dir = createEmptyDir("Project_untitledModifiedNew");
    EXPECT_FALSE(manager.createNewProject(project_dir));

    EXPECT_TRUE(manager.currentProjectDir().empty());
    EXPECT_TRUE(manager.isModified());

    // project directory should be empty
    auto model_json = ModelView::Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_FALSE(ModelView::Utils::exists(model_json));
}

//! Saving of new project. Use untitled+modified project as a starting point.
//! Should fail since project directory is not defined.

TEST_F(ProjectManagerTest, untitledModifiedSave)
{
    ApplicationModels models;
    ProjectManager manager(&models);
    // modifying the model
    models.sample_model->insertItem<ModelView::PropertyItem>();

    EXPECT_FALSE(manager.saveCurrentProject());
    EXPECT_TRUE(manager.isModified());
}

//! Saving of new project. Use untitled+empty project as a starting point.
//! Should be saved, file sould appear on disk.

TEST_F(ProjectManagerTest, untitledModifiedSaveAs)
{
    ApplicationModels models;
    ProjectManager manager(&models);
    models.sample_model->insertItem<ModelView::PropertyItem>(); // modifying the model

    const auto project_dir = createEmptyDir("Project_untitledModifiedSaveAs");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = ModelView::Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(ModelView::Utils::exists(model_json));
}

// ----------------------------------------------------------------------------
// Titled, unmodified
// ----------------------------------------------------------------------------

//! Creating new project. Use titled+unmodified project as a starting point.
//! Should succeed, since old empty project doesn't need to be saved.

TEST_F(ProjectManagerTest, titledUnmodifiedNew)
{
    ApplicationModels models;
    ProjectManager manager(&models);

    const auto project_dir = createEmptyDir("Project_titledUnmodifiedNew");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_EQ(manager.currentProjectDir(), project_dir);

    const auto project_dir2 = createEmptyDir("Project_titledUnmodifiedNew2");
    EXPECT_TRUE(manager.createNewProject(project_dir2));

    EXPECT_EQ(manager.currentProjectDir(), project_dir2);
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = ModelView::Utils::join(project_dir2, samplemodel_name + ".json");
    EXPECT_TRUE(ModelView::Utils::exists(model_json));
}

// ----------------------------------------------------------------------------
// Titled, modified
// ----------------------------------------------------------------------------

//! Saving of new project. Use titled+modified project as a starting point.
//! Should succeed.

TEST_F(ProjectManagerTest, titledModifiedSave)
{
    ApplicationModels models;
    ProjectManager manager(&models);

    const auto project_dir = createEmptyDir("Project_titledModifiedSave");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_EQ(manager.currentProjectDir(), project_dir);

    // modifying the model
    models.sample_model->insertItem<ModelView::PropertyItem>();

    EXPECT_TRUE(manager.saveCurrentProject());
    EXPECT_FALSE(manager.isModified());
}

// ----------------------------------------------------------------------------
// Callbacks
// ----------------------------------------------------------------------------

TEST_F(ProjectManagerTest, callback)
{
    int project_modified_count{0};
    auto on_modified = [&project_modified_count]() { ++project_modified_count; };

    ApplicationModels models;
    ProjectManager manager(&models, on_modified);

    EXPECT_EQ(project_modified_count, 0);

    // saving the project
    const auto project_dir = createEmptyDir("Project_callback");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_EQ(manager.currentProjectDir(), project_dir);
    EXPECT_EQ(project_modified_count, 0);

    // modifying the model
    models.sample_model->insertItem<ModelView::PropertyItem>();
    EXPECT_EQ(project_modified_count, 1);
    EXPECT_TRUE(manager.isModified());

    // modifying the model second time
    models.sample_model->insertItem<ModelView::PropertyItem>();
    EXPECT_EQ(project_modified_count, 1); // do not sum up
    EXPECT_TRUE(manager.isModified());

    EXPECT_TRUE(manager.saveCurrentProject());
    EXPECT_FALSE(manager.isModified());
    EXPECT_EQ(project_modified_count, 1);
}
