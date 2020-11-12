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
#include <mvvm/project/project.h>
#include <mvvm/project/project_types.h>
#include <mvvm/utils/fileutils.h>

using namespace ModelView;

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

class ProjectTest : public FolderBasedTest
{
public:
    ProjectTest()
        : FolderBasedTest("test_ProjectTest")
        , sample_model(std::make_unique<SessionModel>(samplemodel_name))
        , material_model(std::make_unique<SessionModel>(materialmodel_name))
    {
    }
    ~ProjectTest();

    std::vector<SessionModel*> models() const
    {
        return {sample_model.get(), material_model.get()};
    };

    ProjectContext createContext()
    {
        ProjectContext result;
        result.m_models_callback = [this]() { return models(); };
        return result;
    }

    std::unique_ptr<SessionModel> sample_model;
    std::unique_ptr<SessionModel> material_model;
};

ProjectTest::~ProjectTest() = default;

TEST_F(ProjectTest, initialState)
{
    Project project(createContext());
    EXPECT_TRUE(project.projectDir().empty());
    EXPECT_FALSE(project.isModified());
}

//! Testing saveModel.

TEST_F(ProjectTest, saveModel)
{
    Project project(createContext());

    // create project directory and save file
    auto project_dir = createEmptyDir("Untitled1");
    project.save(project_dir);

    EXPECT_EQ(project.projectDir(), project_dir);
    EXPECT_FALSE(project.isModified());

    auto sample_json = Utils::join(project_dir, get_json_filename(samplemodel_name));
    EXPECT_TRUE(Utils::exists(sample_json));

    auto material_json = Utils::join(project_dir, get_json_filename(materialmodel_name));
    EXPECT_TRUE(Utils::exists(material_json));
}

//! Testing loadModel.

TEST_F(ProjectTest, loadModel)
{
    Project project(createContext());

    auto item0 = sample_model->insertItem<PropertyItem>();
    item0->setData(std::string("sample_model_item"));
    auto item0_identifier = item0->identifier();

    auto item1 = material_model->insertItem<PropertyItem>();
    item1->setData(std::string("material_model_item"));
    auto item1_identifier = item1->identifier();

    // create project directory and save file
    auto project_dir = createEmptyDir("Untitled2");

    EXPECT_TRUE(project.isModified());
    project.save(project_dir);
    EXPECT_FALSE(project.isModified());

    EXPECT_EQ(project.projectDir(), project_dir);

    // cleaning models
    sample_model->clear();
    material_model->clear();
    EXPECT_EQ(sample_model->rootItem()->childrenCount(), 0);
    EXPECT_EQ(material_model->rootItem()->childrenCount(), 0);
    EXPECT_TRUE(project.isModified());

    // loading
    project.load(project_dir);
    EXPECT_EQ(sample_model->rootItem()->childrenCount(), 1);
    EXPECT_EQ(material_model->rootItem()->childrenCount(), 1);

    // checking identifiers
    EXPECT_EQ(sample_model->rootItem()->children()[0]->identifier(), item0_identifier);
    EXPECT_EQ(material_model->rootItem()->children()[0]->identifier(), item1_identifier);

    EXPECT_EQ(project.projectDir(), project_dir);
    EXPECT_FALSE(project.isModified());
}
