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

class ProjectManagerTest : public ::testing::Test
{
public:
    ~ProjectManagerTest();

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

    static inline const std::string test_dir = "test_QuickReflProjectManager";
    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }
    std::string testDir() const { return {TestUtils::TestDirectoryPath(test_dir)}; }
};

ProjectManagerTest::~ProjectManagerTest() = default;

TEST_F(ProjectManagerTest, initialState)
{
    ApplicationModels models;
    ProjectManager manager(&models);
    EXPECT_TRUE(manager.currentProjectDir().empty());
}
