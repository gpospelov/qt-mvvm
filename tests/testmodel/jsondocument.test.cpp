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
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/serialization/jsondocument.h>
#include <stdexcept>

using namespace ModelView;

//! Tests JsonDocument class

class JsonDocumentTest : public FolderBasedTest
{
public:
    JsonDocumentTest() : FolderBasedTest("test_JsonDocument") {}
    ~JsonDocumentTest();

    class TestModel1 : public SessionModel
    {
    public:
        TestModel1() : SessionModel("TestModel1") {}
        ~TestModel1();
    };

    class TestModel2 : public SessionModel
    {
    public:
        TestModel2() : SessionModel("TestModel2") {}
        ~TestModel2();
    };
};

JsonDocumentTest::~JsonDocumentTest() = default;
JsonDocumentTest::TestModel1::~TestModel1() = default;
JsonDocumentTest::TestModel2::~TestModel2() = default;

//! Saving the model with content into document and restoring it after.

TEST_F(JsonDocumentTest, saveLoadSingleModel)
{
    auto fileName = TestUtils::TestFileName(testDir(), "saveLoadSingleModel.json");
    SessionModel model("TestModel");
    JsonDocument document({&model});

    // filling model with parent and child
    auto parent = model.insertItem<SessionItem>();
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    const auto parent_identifier = parent->identifier();

    parent->setData(QVariant::fromValue(42));
    auto child = model.insertItem<PropertyItem>(parent);
    child->setDisplayName("child_name");
    const auto child_identifier = child->identifier();

    // saving model in file
    document.save(fileName);

    // modifying model further
    model.removeItem(model.rootItem(), {"", 0});

    // loading model from file
    document.load(fileName);

    // checking that it is as it was right after the save

    // accessing reconstructed parent and child
    auto reco_parent = model.rootItem()->getItem("", 0);
    auto reco_child = reco_parent->getItem("", 0);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->model(), &model);
    EXPECT_EQ(reco_parent->modelType(), Constants::BaseType);
    EXPECT_EQ(reco_parent->parent(), model.rootItem());
    EXPECT_EQ(reco_parent->displayName(), "SessionItem"); // name changed becase of ProjectConverter
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->identifier(), parent_identifier);
    EXPECT_EQ(reco_parent->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->data<int>(), 42);

    // checking child reconstruction
    EXPECT_EQ(reco_child->model(), &model);
    EXPECT_EQ(reco_child->modelType(), Constants::PropertyType);
    EXPECT_EQ(reco_child->parent(), reco_parent);
    EXPECT_EQ(reco_child->displayName(), "Property");
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->identifier(), child_identifier);
    EXPECT_EQ(reco_child->defaultTag(), "");
}

//! Saving two models with content into document and restoring it after.

TEST_F(JsonDocumentTest, saveLoadTwoModels)
{
    auto fileName = TestUtils::TestFileName(testDir(), "saveLoadTwoModels.json");
    TestModel1 model1;
    TestModel2 model2;
    JsonDocument document({&model1, &model2});

    // filling models
    auto parent1 = model1.insertItem<SessionItem>();
    const auto parent_identifier1 = parent1->identifier();

    auto parent2 = model2.insertItem<SessionItem>();
    const auto parent_identifier2 = parent2->identifier();

    // saving models in file
    document.save(fileName);

    // modifying model further
    model1.removeItem(model1.rootItem(), {"", 0});
    model2.removeItem(model2.rootItem(), {"", 0});

    // loading model from file
    document.load(fileName);

    // checking that it is as it was right after the save

    // accessing reconstructed parent and child
    auto reco_parent1 = model1.rootItem()->getItem("", 0);
    auto reco_parent2 = model2.rootItem()->getItem("", 0);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent1->model(), &model1);
    EXPECT_EQ(reco_parent1->parent(), model1.rootItem());
    EXPECT_EQ(reco_parent1->identifier(), parent_identifier1);

    EXPECT_EQ(reco_parent2->model(), &model2);
    EXPECT_EQ(reco_parent2->parent(), model2.rootItem());
    EXPECT_EQ(reco_parent2->identifier(), parent_identifier2);
}

//! Attempt to restore models in wrong order.

TEST_F(JsonDocumentTest, loadModelsInWrongOrder)
{
    auto fileName = TestUtils::TestFileName(testDir(), "loadModelsInWrongOrder.json");
    TestModel1 model1;
    TestModel2 model2;

    // filling models
    auto parent1 = model1.insertItem<SessionItem>();
    const auto parent_identifier1 = parent1->identifier();

    auto parent2 = model2.insertItem<SessionItem>();
    const auto parent_identifier2 = parent2->identifier();

    // saving models in file
    {
        JsonDocument document({&model1, &model2});
        document.save(fileName);
    }

    // modifying model further
    model1.removeItem(model1.rootItem(), {"", 0});
    model2.removeItem(model2.rootItem(), {"", 0});

    JsonDocument document({&model2, &model1}); // intentional wrong order

    // loading model from file
    EXPECT_THROW(document.load(fileName), std::runtime_error);
}
