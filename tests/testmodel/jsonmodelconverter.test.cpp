// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <mvvm/model/itempool.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/serialization/jsonmodelconverter.h>

using namespace ModelView;

//! Checks JsonModel class and its ability to convert SessionModel to json and back.

class JsonModelConverterTest : public ::testing::Test
{
public:
    ~JsonModelConverterTest();

    static const QString test_dir;

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }
};

JsonModelConverterTest::~JsonModelConverterTest() = default;
const QString JsonModelConverterTest::test_dir = "test_JsonModel";

//! Validity of json object representing SessionModel.

TEST_F(JsonModelConverterTest, isValidModel)
{
    JsonModelConverter converter;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter.isSessionModel(object));

    // json object representing valid SessionModel
    QJsonObject object2;
    object2[JsonModelConverter::modelKey] = "abc";
    object2[JsonModelConverter::itemsKey] = QJsonArray();
    EXPECT_TRUE(converter.isSessionModel(object2));
}

//! Creation of json object: empty model.

TEST_F(JsonModelConverterTest, emptyModel)
{
    JsonModelConverter converter;
    SessionModel model("TestModel");

    QJsonObject object;
    converter.model_to_json(model, object);

    EXPECT_EQ(object[JsonModelConverter::modelKey], "TestModel");
    EXPECT_EQ(object[JsonModelConverter::itemsKey].toArray().size(), 0);

    EXPECT_TRUE(converter.isSessionModel(object));
}

//! Empty model to json and back.

TEST_F(JsonModelConverterTest, emptyModelToJsonAndBack)
{
    JsonModelConverter converter;
    SessionModel model("TestModel");

    QJsonObject object;
    converter.model_to_json(model, object);

    // attempt to reconstruct model of different type.
    SessionModel target1("NewModel");
    EXPECT_THROW(converter.json_to_model(object, target1), std::runtime_error);

    // attempt to reconstruct non-empty model
    SessionModel target2("TestModel");
    target2.insertItem<SessionItem>();
    EXPECT_THROW(converter.json_to_model(object, target2), std::runtime_error);

    // succesfull reconstruction
    SessionModel target3("TestModel");
    EXPECT_NO_THROW(converter.json_to_model(object, target3));
    EXPECT_EQ(target3.rootItem()->childrenCount(), 0u);
}

//! Creation of json object: single item in a model.

TEST_F(JsonModelConverterTest, singleItemToJsonAndBack)
{
    JsonModelConverter converter;
    SessionModel model("TestModel");

    auto item = model.insertItem<SessionItem>();

    QJsonObject object;
    converter.model_to_json(model, object);

    // filling new model
    SessionModel target("TestModel");
    converter.json_to_model(object, target);
    EXPECT_EQ(target.rootItem()->childrenCount(), 1u);
    auto reco_item = target.rootItem()->getItem("", 0);
    EXPECT_EQ(reco_item->parent(), target.rootItem());
    EXPECT_EQ(reco_item->modelType(), item->modelType());
}

//! Filling model from json: parent and child in a model to json and back.

TEST_F(JsonModelConverterTest, parentAndChildToJsonAndBack)
{
    JsonModelConverter converter;
    SessionModel model("TestModel");

    // filling original model with content
    auto parent = model.insertItem<SessionItem>();
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    parent->setData(QVariant::fromValue(42));
    auto child = model.insertItem<PropertyItem>(parent);
    child->setDisplayName("child_name");

    // writing model to json
    QJsonObject object;
    converter.model_to_json(model, object);

    // reading model from json
    SessionModel target("TestModel");
    converter.json_to_model(object, target);

    // accessing reconstructed parent and child
    auto reco_parent = target.rootItem()->getItem("", 0);
    auto reco_child = reco_parent->getItem("", 0);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->model(), &target);
    EXPECT_EQ(reco_parent->modelType(), Constants::BaseType);
    EXPECT_EQ(reco_parent->parent(), target.rootItem());
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->data<int>(), 42);

    // checking child reconstruction
    EXPECT_EQ(reco_child->model(), &target);
    EXPECT_EQ(reco_child->modelType(), Constants::PropertyType);
    EXPECT_EQ(reco_child->parent(), reco_parent);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->defaultTag(), "");
}

//! Item in a model to json and back: how persistent are identifiers.

TEST_F(JsonModelConverterTest, identifiers)
{
    JsonModelConverter converter;
    auto pool1 = std::make_shared<ItemPool>();

    // creating model and converting it to json
    SessionModel source("SourceModel", pool1);
    auto parent1 = source.insertItem<SessionItem>();
    QJsonObject json_source;
    converter.model_to_json(source, json_source);

    // creating source and filling it from json
    auto pool2 = std::make_shared<ItemPool>();
    SessionModel target("SourceModel", pool2);
    converter.json_to_model(json_source, target);
    auto reco_parent = target.rootItem()->getItem("", 0);

    // comparing identifiers of two items from different models
    auto id1 = parent1->identifier();
    auto id2 = reco_parent->identifier();
    EXPECT_EQ(id1, id2);

    // saving target in its own json
    QJsonObject json_target;
    converter.model_to_json(target, json_target);

    // comparing text representations of two json
    EXPECT_EQ(TestUtils::JsonToString(json_source), TestUtils::JsonToString(json_target));

    // checking item registrations
    EXPECT_EQ(pool1->item_for_key(id1), parent1);
    EXPECT_EQ(pool2->item_for_key(id2), reco_parent);
}

//! Filling model from json: parent and child in a model to json and back.

TEST_F(JsonModelConverterTest, parentAndChildToFileAndBack)
{
    JsonModelConverter converter;
    SessionModel model("TestModel");

    // filling original model with content
    auto parent = model.insertItem<SessionItem>();
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    parent->setData(QVariant::fromValue(42));
    auto child = model.insertItem<PropertyItem>(parent);
    child->setDisplayName("child_name");

    // writing model to json
    auto object = std::make_unique<QJsonObject>();
    converter.model_to_json(model, *object);

    // saving object to file
    auto fileName = TestUtils::TestFileName(test_dir, "model.json");
    TestUtils::SaveJson(*object, fileName);
    object.reset();

    // converting document back to item
    auto document = TestUtils::LoadJson(fileName);
    SessionModel target("TestModel");
    converter.json_to_model(document.object(), target);

    // accessing reconstructed parent and child
    auto reco_parent = target.rootItem()->getItem("", 0);
    auto reco_child = reco_parent->getItem("", 0);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->model(), &target);
    EXPECT_EQ(reco_parent->modelType(), Constants::BaseType);
    EXPECT_EQ(reco_parent->parent(), target.rootItem());
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->data<int>(), 42);

    // checking child reconstruction
    EXPECT_EQ(reco_child->model(), &target);
    EXPECT_EQ(reco_child->modelType(), Constants::PropertyType);
    EXPECT_EQ(reco_child->parent(), reco_parent);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->defaultTag(), "");
}
