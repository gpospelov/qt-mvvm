// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/project/projectutils.h"

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include "mvvm/interfaces/projectinterface.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/project/project_types.h"

using namespace ModelView;

//! Tests of ProjectUtils namespace functions.

class ProjectUtilsTest : public FolderBasedTest {
public:
    ProjectUtilsTest()
        : FolderBasedTest("test_ProjectUtils")
        , sample_model(std::make_unique<SessionModel>("SampleModel"))
    {
    }

    std::vector<SessionModel*> models() const { return {sample_model.get()}; };

    ProjectContext createContext()
    {
        ProjectContext result;
        result.m_models_callback = [this]() { return models(); };
        return result;
    }

    std::unique_ptr<SessionModel> sample_model;
};

//! Testing helper structure.

TEST_F(ProjectUtilsTest, SuggestFileName)
{
    SessionModel model("TestModel");
    EXPECT_EQ(std::string("testmodel.json"), ProjectUtils::SuggestFileName(model));
}

TEST_F(ProjectUtilsTest, CreateUntitledProject)
{
    auto project = ProjectUtils::CreateUntitledProject(createContext());
    EXPECT_TRUE(project->projectDir().empty());
}

TEST_F(ProjectUtilsTest, ProjectWindowTitle)
{
    auto project = ProjectUtils::CreateUntitledProject(createContext());

    // unmodified project without projectDir
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), "Untitled");

    sample_model->insertItem<PropertyItem>();
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), "*Untitled");

    // saving in a project directory
    project->save(testPath());
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), testDir());

    // modifying
    sample_model->insertItem<PropertyItem>();
    EXPECT_EQ(ProjectUtils::ProjectWindowTitle(*project), "*" + testDir());
}

TEST_F(ProjectUtilsTest, IsPossibleProjectDir)
{
    auto project = ProjectUtils::CreateUntitledProject(createContext());

    // empty directory can't be a project directory
    auto dirname = createEmptyDir("test_IsPossibleProjectDir");
    EXPECT_FALSE(ProjectUtils::IsPossibleProjectDir(dirname));

    project->save(dirname);
    EXPECT_TRUE(ProjectUtils::IsPossibleProjectDir(dirname));
}
