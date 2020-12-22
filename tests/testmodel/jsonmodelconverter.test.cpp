// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonmodelconverter.h"

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include "mvvm/model/itempool.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionitemtags.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/taginfo.h"
#include "mvvm/serialization/jsonitem_types.h"
#include "mvvm/serialization/jsonitemformatassistant.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <stdexcept>

using namespace ModelView;

//! Checks JsonModel class and its ability to convert SessionModel to json and back.

class JsonModelConverterTest : public FolderBasedTest {
public:
    JsonModelConverterTest() : FolderBasedTest("test_JsonModelConverter") {}
};

//! Creation of json object: empty model.

TEST_F(JsonModelConverterTest, emptyModel)
{
    JsonModelConverter converter(ConverterMode::project);
    SessionModel model("TestModel");

    QJsonObject object = converter.to_json(model);

    EXPECT_EQ(object[JsonItemFormatAssistant::sessionModelKey], "TestModel");
    EXPECT_EQ(object[JsonItemFormatAssistant::itemsKey].toArray().size(), 0);

    JsonItemFormatAssistant assistant;
    EXPECT_TRUE(assistant.isSessionModel(object));
}

//! Empty model to json and back.

TEST_F(JsonModelConverterTest, emptyModelToJsonAndBack)
{
    JsonModelConverter converter(ConverterMode::project);
    SessionModel model("TestModel");

    QJsonObject object = converter.to_json(model);

    // attempt to reconstruct model of different type.
    SessionModel target1("NewModel");
    EXPECT_THROW(converter.from_json(object, target1), std::runtime_error);

    // attempt to reconstruct non-empty model
    SessionModel target2("TestModel");
    target2.insertItem<SessionItem>();
    EXPECT_NO_THROW(converter.from_json(object, target2));

    // succesfull reconstruction
    SessionModel target3("TestModel");
    EXPECT_NO_THROW(converter.from_json(object, target3));
    EXPECT_EQ(target3.rootItem()->childrenCount(), 0u);
}

//! Creation of json object: single item in a model.

TEST_F(JsonModelConverterTest, singleItemToJsonAndBack)
{
    JsonModelConverter converter(ConverterMode::project);
    SessionModel model("TestModel");

    auto item = model.insertItem<SessionItem>();

    QJsonObject object = converter.to_json(model);

    // filling new model
    SessionModel target("TestModel");
    converter.from_json(object, target);
    EXPECT_EQ(target.rootItem()->childrenCount(), 1u);
    auto reco_item = target.rootItem()->getItem("", 0);
    EXPECT_EQ(reco_item->parent(), target.rootItem());
    EXPECT_EQ(reco_item->modelType(), item->modelType());
}

//! Filling model from json: parent and child in a model to json and back.

TEST_F(JsonModelConverterTest, parentAndChildToJsonAndBack)
{
    JsonModelConverter converter(ConverterMode::project);
    SessionModel model("TestModel");

    // filling original model with content
    auto parent = model.insertItem<SessionItem>();
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    parent->setData(QVariant::fromValue(42));
    auto child = model.insertItem<PropertyItem>(parent);
    child->setDisplayName("child_name");

    // writing model to json
    QJsonObject object = converter.to_json(model);

    // reading model from json
    SessionModel target("TestModel");
    converter.from_json(object, target);

    // accessing reconstructed parent and child
    auto reco_parent = target.rootItem()->getItem("", 0);
    auto reco_child = reco_parent->getItem("", 0);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->model(), &target);
    EXPECT_EQ(reco_parent->modelType(), Constants::BaseType);
    EXPECT_EQ(reco_parent->parent(), target.rootItem());
    EXPECT_EQ(reco_parent->displayName(),
              "SessionItem"); // Name changed because of ProjectConverter
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->itemTags()->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->data<int>(), 42);

    // checking child reconstruction
    EXPECT_EQ(reco_child->model(), &target);
    EXPECT_EQ(reco_child->modelType(), Constants::PropertyType);
    EXPECT_EQ(reco_child->parent(), reco_parent);
    EXPECT_EQ(reco_child->displayName(), "Property"); // // Name changed because of ProjectConverter
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->itemTags()->defaultTag(), "");
}

//! Item in a model to json and back: how persistent are identifiers.

TEST_F(JsonModelConverterTest, identifiers)
{
    JsonModelConverter converter(ConverterMode::project);
    auto pool1 = std::make_shared<ItemPool>();

    // creating model and converting it to json
    SessionModel source("SourceModel", pool1);
    auto parent1 = source.insertItem<SessionItem>();
    QJsonObject json_source = converter.to_json(source);

    // creating source and filling it from json
    auto pool2 = std::make_shared<ItemPool>();
    SessionModel target("SourceModel", pool2);
    converter.from_json(json_source, target);
    auto reco_parent = target.rootItem()->getItem("", 0);

    // comparing identifiers of two items from different models
    auto id1 = parent1->identifier();
    auto id2 = reco_parent->identifier();
    EXPECT_EQ(id1, id2);

    // saving target in its own json
    QJsonObject json_target = converter.to_json(target);

    // comparing text representations of two json
    EXPECT_EQ(TestUtils::JsonToString(json_source), TestUtils::JsonToString(json_target));

    // checking item registrations
    EXPECT_EQ(pool1->item_for_key(id1), parent1);
    EXPECT_EQ(pool2->item_for_key(id2), reco_parent);
}

//! Filling model from json: parent and child in a model to json and back.

TEST_F(JsonModelConverterTest, parentAndChildToFileAndBack)
{
    JsonModelConverter converter(ConverterMode::project);
    SessionModel model("TestModel");

    // filling original model with content
    auto parent = model.insertItem<SessionItem>();
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);

    parent->setData(QVariant::fromValue(42));
    auto child = model.insertItem<PropertyItem>(parent);
    child->setDisplayName("child_name");

    // writing model to json
    auto object = converter.to_json(model);

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "model.json");
    TestUtils::SaveJson(object, fileName);

    // converting document back to item
    auto document = TestUtils::LoadJson(fileName);
    SessionModel target("TestModel");
    converter.from_json(document.object(), target);

    // accessing reconstructed parent and child
    auto reco_parent = target.rootItem()->getItem("", 0);
    auto reco_child = reco_parent->getItem("", 0);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->model(), &target);
    EXPECT_EQ(reco_parent->modelType(), Constants::BaseType);
    EXPECT_EQ(reco_parent->parent(), target.rootItem());
    EXPECT_EQ(reco_parent->displayName(), "SessionItem");
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->itemTags()->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->data<int>(), 42);

    // checking child reconstruction
    EXPECT_EQ(reco_child->model(), &target);
    EXPECT_EQ(reco_child->modelType(), Constants::PropertyType);
    EXPECT_EQ(reco_child->parent(), reco_parent);
    EXPECT_EQ(reco_child->displayName(), "Property");
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->itemTags()->defaultTag(), "");
}

//! Creation of json object (single item in a model), then writing same json object back
//! to model without emptying it. Real bug case: check if unsubscribtion mechanism works.

TEST_F(JsonModelConverterTest, singleItemToJsonAndBackToSameModel)
{
    auto pool = std::make_shared<ItemPool>();

    JsonModelConverter converter(ConverterMode::project);
    SessionModel model("TestModel", pool);
    auto item = model.insertItem<SessionItem>();

    auto root_item = model.rootItem();
    auto root_id = root_item->identifier();
    auto item_id = item->identifier();

    QJsonObject object = converter.to_json(model);

    // filling new model
    converter.from_json(object, model);

    EXPECT_EQ(pool->size(), 2);
    EXPECT_FALSE(pool->item_for_key(root_id) == model.rootItem()); // old root identifier has gone
    EXPECT_TRUE(model.rootItem() != root_item);                    // old root item gone

    auto new_item = model.rootItem()->children().at(0);
    EXPECT_EQ(pool->item_for_key(item_id), new_item);
}
