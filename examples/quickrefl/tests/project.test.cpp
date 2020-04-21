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
#include "project.h"
#include "test_utils.h"
#include <filesystem>
#include <mvvm/model/sessionmodel.h>

namespace
{
const std::string samplemodel_name = "samplemodel";
}

//! Tests for Project class.

class ProjectTest : public ::testing::Test
{
public:
    ~ProjectTest();

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

    static inline const std::string test_dir = "test_QuickReflProject";

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }

    std::filesystem::path test_path() const
    {
        return {TestUtils::TestDirectoryPath(test_dir)};
    }
};

ProjectTest::~ProjectTest() = default;

//! Testing helper structure.

TEST_F(ProjectTest, saveModel)
{
    ApplicationModels models;
    Project project(&models);

    std::filesystem::path project_path = test_path() / "Untitled1";
    std::filesystem::remove_all(project_path);
    std::filesystem::create_directory(project_path);

    project.save(project_path.string());

    EXPECT_TRUE(std::filesystem::exists(project_path / "samplemodel.json"));
}
