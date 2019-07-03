#include "google_test.h"
#include "jsonitemconverter.h"
#include "propertyitem.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include "test_utils.h"
#include "itemmanager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace ModelView;

//! Checks JsonItem class and its ability to convert SessionItems to json and back.

class TestJsonItemConverter : public ::testing::Test
{
public:
    TestJsonItemConverter() : m_model(std::make_unique<SessionModel>()) {}
    ~TestJsonItemConverter();

    static const QString test_dir;

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }

    std::unique_ptr<JsonItemConverter> createConverter()
    {
        return std::make_unique<JsonItemConverter>(m_model->manager()->factory());
    }

private:
    std::unique_ptr<SessionModel> m_model;
};

TestJsonItemConverter::~TestJsonItemConverter() = default;
const QString TestJsonItemConverter::test_dir = "test_JsonItemConverter";

//! Checks the validity of json object representing SessionItem.

TEST_F(TestJsonItemConverter, isSessionItem)
{
    auto converter = createConverter();

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter->isSessionItem(object));

    // it also should contain array
    object[JsonItemConverter::modelKey] = "abc";
    object[JsonItemConverter::itemDataKey] = QJsonArray();
    object[JsonItemConverter::itemTagsKey] = 42; // intentionally incorrect
    EXPECT_FALSE(converter->isSessionItem(object));

    // correctly constructed
    object[JsonItemConverter::itemTagsKey] = QJsonObject();
    EXPECT_TRUE(converter->isSessionItem(object));
}

//! Checks the validity of json object representing SessionItemTags.

TEST_F(TestJsonItemConverter, isSessionItemTags)
{
    auto converter = createConverter();

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter->isSessionItemTags(object));

    // it also should contain array
    object[JsonItemConverter::defaultTagKey] = "abc";
    object[JsonItemConverter::containerKey] = QJsonArray();
    EXPECT_TRUE(converter->isSessionItemTags(object));
}

//! Checks the validity of json object representing SessionItemContainer.

TEST_F(TestJsonItemConverter, isSessionItemContainer)
{
    auto converter = createConverter();

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter->isSessionItemContainer(object));

    // it also should contain array
    object[JsonItemConverter::tagInfoKey] = QJsonObject();
    object[JsonItemConverter::itemsKey] = QJsonArray();
    EXPECT_TRUE(converter->isSessionItemContainer(object));
}

//! PropertyItem to json object.

TEST_F(TestJsonItemConverter, propertyItemToJson)
{
    auto converter = createConverter();

    PropertyItem item;
    auto object = converter->to_json(&item);

    // this object represents SessionItem
    EXPECT_TRUE(converter->isSessionItem(object));
}

//! PropertyItem to json object and back.

TEST_F(TestJsonItemConverter, propertyItemToJsonAndBack)
{
    auto converter = createConverter();

    PropertyItem item;
    auto object = converter->to_json(&item);

    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->identifier(), item.identifier());
}

//! PropertyItem to json file and back.

TEST_F(TestJsonItemConverter, propertyItemToFileAndBack)
{
    auto converter = createConverter();

    PropertyItem item;
    auto object = converter->to_json(&item);

    // saving object to file
    auto fileName = TestUtils::TestFileName(test_dir, "propertyitem.json");
    TestUtils::SaveJson(object, fileName);

    auto document = TestUtils::LoadJson(fileName);
    auto reco = converter->from_json(document.object());

    EXPECT_EQ(reco->parent(), nullptr);
    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->identifier(), item.identifier());
}

//! Parent and child to json object.

TEST_F(TestJsonItemConverter, parentAndChildToJsonAndBack)
{
    auto converter = createConverter();
    const std::string model(Constants::BaseType);

    auto parent = std::make_unique<SessionItem>(model);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child = new SessionItem(model);
    child->setDisplayName("child_name");
    parent->insertItem(child, "", -1);

    // converting to json
    auto object = converter->to_json(parent.get());
    EXPECT_TRUE(converter->isSessionItem(object));

    // converting json back to item
    auto reco_parent = converter->from_json(object);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->modelType(), model);
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->model(), nullptr);

    // checking child reconstruction
    auto reco_child = reco_parent->getItem("defaultTag");
    EXPECT_EQ(reco_child->parent(), reco_parent.get());
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->modelType(), model);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->defaultTag(), "");
}

//! Parent and child to json file and back.

TEST_F(TestJsonItemConverter, parentAndChildToFileAndBack)
{
    auto converter = createConverter();
    const std::string model(Constants::BaseType);

    auto parent = std::make_unique<SessionItem>(model);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child = new SessionItem(model);
    child->setDisplayName("child_name");
    parent->insertItem(child, "", -1);

    // converting to json
    auto object = converter->to_json(parent.get());
    EXPECT_TRUE(converter->isSessionItem(object));

    // saving object to file
    auto fileName = TestUtils::TestFileName(test_dir, "parentandchild.json");
    TestUtils::SaveJson(object, fileName);

    // converting document back to item
    auto document = TestUtils::LoadJson(fileName);
    auto reco_parent = converter->from_json(document.object());

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->modelType(), model);
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->model(), nullptr);

    // checking child reconstruction
    auto reco_child = reco_parent->getItem("defaultTag");
    EXPECT_EQ(reco_child->parent(), reco_parent.get());
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->modelType(), model);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->defaultTag(), "");
}
