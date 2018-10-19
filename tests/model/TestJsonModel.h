#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "jsonmodel.h"
#include "sessionitem.h"
#include "test_utils.h"
#include "itemmanager.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

//! Checks JsonModel class and its ability to convert SessionModel to json and back.

class TestJsonModel : public ::testing::Test
{
public:
    ~TestJsonModel();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }
};

TestJsonModel::~TestJsonModel() = default;
const QString TestJsonModel::test_dir = "test_JsonModel";

//! Checks the validity of json object representing item tree.

TEST_F(TestJsonModel, isValidItem)
{
    JsonModel converter;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter.is_item(object));

    // it also should contain array
    object[JsonModel::modelKey] = "abc";
    object[JsonModel::itemsKey] = 42; // incorrect
    object[JsonModel::itemDataKey] = QJsonArray();
    EXPECT_FALSE(converter.is_item(object));

    // correctly constructed
    object[JsonModel::itemsKey] = QJsonArray();
    object[JsonModel::itemDataKey] = QJsonArray();
    EXPECT_TRUE(converter.is_item(object));

    // wrong extra key in json
    object["abc"] = "abc";
    EXPECT_FALSE(converter.is_item(object));
    EXPECT_FALSE(converter.is_item(object));
}

//! Checks creation of json object: single item (no children) without the data.

TEST_F(TestJsonModel, singleItem)
{
    const QString model_type("MultiLayer");

    JsonModel converter;
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));

    QJsonObject object;
    converter.item_to_json(parent.get(), object);

    EXPECT_EQ(object[JsonModel::modelKey], model_type);
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 0);
    EXPECT_EQ(object[JsonModel::itemDataKey].toArray().size(), 0);
}

//! Checks creation of json object: parent item with one data variant and one child on board.

TEST_F(TestJsonModel, parentAndChild)
{
    const QString model_type("MultiLayer");
    JsonModel converter;

    // constructing multilayer
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));
    parent->setData(QVariant::fromValue(42), 1);
    auto child = new SessionItem("Layer");
    parent->insertItem(-1, child);

    QJsonObject object;
    converter.item_to_json(parent.get(), object);

    EXPECT_EQ(object[JsonModel::modelKey], model_type);
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 1);
    EXPECT_EQ(object[JsonModel::itemDataKey].toArray().size(), 1);

    // saving to file
    auto fileName = TestUtils::TestFileName(test_dir, "items.json");
    TestUtils::SaveJson(object, fileName);
}

//! Validity of json object representing SessionModel.

TEST_F(TestJsonModel, isValidModel)
{
    JsonModel converter;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter.is_model(object));

    // json object representing SessionItem can not represent the model
    object[JsonModel::modelKey] = "abc";
    object[JsonModel::itemsKey] = QJsonArray();
    object[JsonModel::itemDataKey] = QJsonArray();
    EXPECT_FALSE(converter.is_model(object));

    // json object representing valid SessionModel
    QJsonObject object2;
    object2[JsonModel::modelKey] = "abc";
    object2[JsonModel::itemsKey] = QJsonArray();
    EXPECT_TRUE(converter.is_model(object2));
}

//! Creation of json object: empty model.

TEST_F(TestJsonModel, emptyModel)
{
    JsonModel converter;
    SessionModel model("TestModel");

    QJsonObject object;
    converter.model_to_json(model, object);

    EXPECT_EQ(object[JsonModel::modelKey], "TestModel");
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 0);
}

//! Creation of json object: single item in a model.

TEST_F(TestJsonModel, singleItemInModel)
{
    JsonModel converter;
    SessionModel model("TestModel");

    model.insertNewItem("abc", nullptr, -1);

    QJsonObject object;
    converter.model_to_json(model, object);

    EXPECT_EQ(object[JsonModel::modelKey], QString::fromStdString(model.modelType()));
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 1);
}

//! Creation of json object: parent and child in a model.

TEST_F(TestJsonModel, parentAndChildInModel)
{
    JsonModel converter;
    SessionModel model("TestModel");

    auto parent = model.insertNewItem("MultiLayer");
    parent->setData(QVariant::fromValue(42), 1);
    auto child = model.insertNewItem("Layer", parent);

    QJsonObject object;
    converter.model_to_json(model, object);

    EXPECT_EQ(object[JsonModel::modelKey], QString::fromStdString(model.modelType()));
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 1);

    // saving to file
    auto fileName = TestUtils::TestFileName(test_dir, "model.json");
    TestUtils::SaveJson(object, fileName);
}

//! Filling model from json: empty model to json and then back.

TEST_F(TestJsonModel, emptyModelFromJson)
{
    JsonModel converter;
    SessionModel model("TestModel");

    QJsonObject object;
    converter.model_to_json(model, object);

    // attempt to reconstruct model of different type.
    SessionModel target1("NewModel");
    EXPECT_THROW(converter.json_to_model(object, target1), std::runtime_error);

    // attempt to reconstruct non-empty model
    SessionModel target2("TestModel");
    target2.insertNewItem("Layer");
    EXPECT_THROW(converter.json_to_model(object, target2), std::runtime_error);

    // succesfull reconstruction
    SessionModel target3("TestModel");
    EXPECT_NO_THROW(converter.json_to_model(object, target3));
    EXPECT_EQ(target3.rootItem()->childrenCount(), 0u);
}

//! Filling model from json: parent and child in a model to json and back.

TEST_F(TestJsonModel, parentAndChildModelFromJson)
{
    JsonModel converter;
    SessionModel model("TestModel");

    // filling original model with content
    auto parent = model.insertNewItem("MultiLayer");
    parent->setData(QVariant::fromValue(42), 1);
    auto child = model.insertNewItem("Layer", parent);

    // writing model to json
    QJsonObject object;
    converter.model_to_json(model, object);

    // reading model from json
    SessionModel target("TestModel");
    converter.json_to_model(object, target);

    // checking target model
    EXPECT_EQ(target.rootItem()->childrenCount(), 1u);
    auto parent2 = target.rootItem()->childAt(0);
    EXPECT_EQ(parent2->childrenCount(), 1u);
    EXPECT_EQ(parent2->modelType(), "MultiLayer");
    EXPECT_EQ(parent2->data(1), 42);
    auto child2 = parent2->childAt(0);
    EXPECT_EQ(child2->childrenCount(), 0u);
    EXPECT_EQ(child2->modelType(), "Layer");
}

//! Item in a model to json and back: how persistent are identifiers.

TEST_F(TestJsonModel, identifiers)
{
    // creating model and converting it to json
    SessionModel source("SourceModel");
    auto parent1 = source.insertNewItem("MultiLayer");
    QJsonObject json_source;
    source.manager()->converter().model_to_json(source, json_source);

    // creating source and filling it from json
    SessionModel target("SourceModel");
    target.manager()->converter().json_to_model(json_source, target);
    auto parent2 = target.rootItem()->childAt(0);

    // comparing identifiers of two items from different models
    auto id1 = parent1->data(ItemDataRole::IDENTIFIER).value<std::string>();
    auto id2 = parent2->data(ItemDataRole::IDENTIFIER).value<std::string>();
    EXPECT_EQ(id1, id2);

    // saving target in its own json
    QJsonObject json_target;
    target.manager()->converter().model_to_json(target, json_target);

    // comparing text representations of two json
    EXPECT_EQ(TestUtils::JsonToString(json_source), TestUtils::JsonToString(json_target));

    // checking item registrations
    EXPECT_EQ(source.manager()->findItem(id1), parent1);
    EXPECT_EQ(target.manager()->findItem(id2), parent2);
}
