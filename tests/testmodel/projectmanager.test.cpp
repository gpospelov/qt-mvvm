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
#include "test_utils.h"
#include <cctype>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/project/project_types.h>
#include <mvvm/project/projectmanager.h>
#include <mvvm/utils/fileutils.h>

using namespace ModelView;

namespace
{
const std::string samplemodel_name = "samplemodel";

} // namespace

//! Tests for ProjectManager class.

class ProjectManagerTest : public FolderBasedTest
{
public:
    ProjectManagerTest()
        : FolderBasedTest("test_ProjectManager")
        , sample_model(std::make_unique<ModelView::SessionModel>(samplemodel_name))
    {
    }
    ~ProjectManagerTest();

    std::vector<SessionModel*> models() const { return {sample_model.get()}; };

    ProjectContext createContext()
    {
        ProjectContext result;
        result.m_models_callback = [this]() { return models(); };
        return result;
    }

    std::unique_ptr<SessionModel> sample_model;
};

ProjectManagerTest::~ProjectManagerTest() = default;

//! Initial state of ProjectManager. Project created, and not-saved.

TEST_F(ProjectManagerTest, initialState)
{
    ProjectManager manager(createContext());
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
    ProjectManager manager(createContext());

    const auto project_dir = createEmptyDir("Project_untitledEmptyNew");
    EXPECT_TRUE(manager.createNewProject(project_dir));

    EXPECT_EQ(manager.currentProjectDir(), project_dir);
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));
}

//! Saving of new project. Use untitled+empty project as a starting point.
//! Should fail since project directory is not defined.

TEST_F(ProjectManagerTest, untitledEmptySave)
{
    ProjectManager manager(createContext());
    EXPECT_FALSE(manager.saveCurrentProject());
    EXPECT_FALSE(manager.isModified());
}

//! Saving of new project. Use untitled+empty project as a starting point.
//! Should be saved, file sould appear on disk.

TEST_F(ProjectManagerTest, untitledEmptySaveAs)
{
    ProjectManager manager(createContext());

    const auto project_dir = createEmptyDir("Project_untitledEmptySaveAs");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));
}

// ----------------------------------------------------------------------------
// Untitled, modified
// ----------------------------------------------------------------------------

//! Creating new project. Use untitled+modified project as a starting point.
//! Should fail, since modified old project will prevent creation of the new one.

TEST_F(ProjectManagerTest, untitledModifiedNew)
{
    ProjectManager manager(createContext());

    // modifying the model
    sample_model->insertItem<PropertyItem>();

    EXPECT_TRUE(manager.isModified());

    const auto project_dir = createEmptyDir("Project_untitledModifiedNew");
    EXPECT_FALSE(manager.createNewProject(project_dir));

    EXPECT_TRUE(manager.currentProjectDir().empty());
    EXPECT_TRUE(manager.isModified());

    // project directory should be empty
    auto model_json = Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_FALSE(Utils::exists(model_json));
}

//! Saving of new project. Use untitled+modified project as a starting point.
//! Should fail since project directory is not defined.

TEST_F(ProjectManagerTest, untitledModifiedSave)
{
    ProjectManager manager(createContext());
    // modifying the model
    sample_model->insertItem<PropertyItem>();

    EXPECT_FALSE(manager.saveCurrentProject());
    EXPECT_TRUE(manager.isModified());
}

//! Saving of new project. Use untitled+empty project as a starting point.
//! Should be saved, file sould appear on disk.

TEST_F(ProjectManagerTest, untitledModifiedSaveAs)
{
    ProjectManager manager(createContext());
    sample_model->insertItem<PropertyItem>(); // modifying the model

    const auto project_dir = createEmptyDir("Project_untitledModifiedSaveAs");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = Utils::join(project_dir, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));
}

// ----------------------------------------------------------------------------
// Titled, unmodified
// ----------------------------------------------------------------------------

//! Creating new project. Use titled+unmodified project as a starting point.
//! Should succeed, since old empty project doesn't need to be saved.

TEST_F(ProjectManagerTest, titledUnmodifiedNew)
{
    ProjectManager manager(createContext());

    const auto project_dir = createEmptyDir("Project_titledUnmodifiedNew");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_EQ(manager.currentProjectDir(), project_dir);

    const auto project_dir2 = createEmptyDir("Project_titledUnmodifiedNew2");
    EXPECT_TRUE(manager.createNewProject(project_dir2));

    EXPECT_EQ(manager.currentProjectDir(), project_dir2);
    EXPECT_FALSE(manager.isModified());

    // project directory should contain a json file with the model
    auto model_json = Utils::join(project_dir2, samplemodel_name + ".json");
    EXPECT_TRUE(Utils::exists(model_json));
}

// ----------------------------------------------------------------------------
// Titled, modified
// ----------------------------------------------------------------------------

//! Saving of new project. Use titled+modified project as a starting point.
//! Should succeed.

TEST_F(ProjectManagerTest, titledModifiedSave)
{
    ProjectManager manager(createContext());

    const auto project_dir = createEmptyDir("Project_titledModifiedSave");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_EQ(manager.currentProjectDir(), project_dir);

    // modifying the model
    sample_model->insertItem<PropertyItem>();

    EXPECT_TRUE(manager.saveCurrentProject());
    EXPECT_FALSE(manager.isModified());
}

// ----------------------------------------------------------------------------
// Callbacks
// ----------------------------------------------------------------------------

TEST_F(ProjectManagerTest, callback)
{
    int project_modified_count{0};

    auto context = createContext();
    context.m_modified_callback = [&project_modified_count]() { ++project_modified_count; };

    ProjectManager manager(context);

    EXPECT_EQ(project_modified_count, 0);

    // saving the project
    const auto project_dir = createEmptyDir("Project_callback");
    EXPECT_TRUE(manager.saveProjectAs(project_dir));
    EXPECT_EQ(manager.currentProjectDir(), project_dir);
    EXPECT_EQ(project_modified_count, 0);

    // modifying the model
    sample_model->insertItem<PropertyItem>();
    EXPECT_EQ(project_modified_count, 1);
    EXPECT_TRUE(manager.isModified());

    // modifying the model second time
    sample_model->insertItem<PropertyItem>();
    EXPECT_EQ(project_modified_count, 1); // do not sum up
    EXPECT_TRUE(manager.isModified());

    EXPECT_TRUE(manager.saveCurrentProject());
    EXPECT_FALSE(manager.isModified());
    EXPECT_EQ(project_modified_count, 1);
}
