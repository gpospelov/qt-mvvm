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
#include <cctype>
#include <filesystem>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/propertyitem.h>

namespace
{
const std::string samplemodel_name = "SampleModel";
const std::string materialmodel_name = "MaterialModel";

//! Constructs json file name from SessionModel typeName (as it is done internaly by Project).
std::string get_json_filename(const std::string& model_name)
{
    std::string result(model_name);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result + ".json";
}

} // namespace

//! Tests for Project class.

class ProjectTest : public ::testing::Test
{
public:
    ~ProjectTest();

    class ApplicationModels : public ApplicationModelsInterface
    {
    public:
        std::unique_ptr<ModelView::SessionModel> sample_model;
        std::unique_ptr<ModelView::SessionModel> material_model;
        ApplicationModels()
            : sample_model(std::make_unique<ModelView::SessionModel>(samplemodel_name)),
              material_model(std::make_unique<ModelView::SessionModel>(materialmodel_name))
        {
        }

        std::vector<ModelView::SessionModel*> persistent_models() const override
        {
            return {sample_model.get(), material_model.get()};
        };
    };

    static inline const std::string test_dir = "test_QuickReflProject";

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }

    std::filesystem::path test_path() const { return {TestUtils::TestDirectoryPath(test_dir)}; }

    //! Create project directory in test directory.
    //! Remove recursively previous one with same name, if exist.
    std::string create_project_dir(const std::string& name)
    {
        std::filesystem::path project_path = test_path() / name;
        std::filesystem::remove_all(project_path);
        std::filesystem::create_directory(project_path);
        return project_path.string();
    }
};

ProjectTest::~ProjectTest() = default;

//! Testing saveModel.

TEST_F(ProjectTest, saveModel)
{
    ApplicationModels models;
    Project project(&models);

    // create project directory and save file
    auto project_dir = create_project_dir("Untitled1");
    project.save(project_dir);

    auto sample_json = std::filesystem::path(project_dir) / get_json_filename(samplemodel_name);
    EXPECT_TRUE(std::filesystem::exists(sample_json));

    auto material_json = std::filesystem::path(project_dir) / get_json_filename(materialmodel_name);
    EXPECT_TRUE(std::filesystem::exists(material_json));
}

//! Testing loadModel.

TEST_F(ProjectTest, loadModel)
{
    ApplicationModels models;
    Project project(&models);

    auto item0 = models.sample_model->insertItem<ModelView::PropertyItem>();
    item0->setData(std::string("sample_model_item"));
    auto item0_identifier = item0->identifier();

    auto item1 = models.material_model->insertItem<ModelView::PropertyItem>();
    item1->setData(std::string("material_model_item"));
    auto item1_identifier = item1->identifier();

    // create project directory and save file
    auto project_dir = create_project_dir("Untitled2");
    project.save(project_dir);

    // cleaning models
    models.sample_model->clear();
    models.material_model->clear();
    EXPECT_EQ(models.sample_model->rootItem()->childrenCount(), 0);
    EXPECT_EQ(models.material_model->rootItem()->childrenCount(), 0);

    // loading
    project.load(project_dir);
    EXPECT_EQ(models.sample_model->rootItem()->childrenCount(), 1);
    EXPECT_EQ(models.material_model->rootItem()->childrenCount(), 1);

    // checking identifiers
    EXPECT_EQ(models.sample_model->rootItem()->children()[0]->identifier(), item0_identifier);
    EXPECT_EQ(models.material_model->rootItem()->children()[0]->identifier(), item1_identifier);
}
