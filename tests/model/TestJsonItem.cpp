#include "google_test.h"
#include "sessionmodel.h"
#include "jsonitem.h"
#include "sessionitem.h"
#include "test_utils.h"
#include "taginfo.h"
#include <QJsonObject>
#include <QJsonArray>

using namespace ModelView;

//! Checks JsonItem class and its ability to convert SessionItems to json and back.

class TestJsonItem : public ::testing::Test
{
public:
    TestJsonItem() : m_model(std::make_unique<SessionModel>())
    {

    }
    ~TestJsonItem();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }

    std::unique_ptr<JsonItem> createConverter()
    {
        return std::make_unique<JsonItem>(m_model.get());
    }

private:
    std::unique_ptr<SessionModel> m_model;
};

TestJsonItem::~TestJsonItem() = default;
const QString TestJsonItem::test_dir = "test_JsonItem";

//! Checks the validity of json object representing SessionItem.

TEST_F(TestJsonItem, isSessionItem)
{
    auto converter = createConverter();

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter->isSessionItem(object));

    // it also should contain array
    object[JsonItem::modelKey] = "abc";
    object[JsonItem::itemDataKey] = QJsonArray();
    object[JsonItem::itemTagsKey] = 42; // intentionally incorrect
    EXPECT_FALSE(converter->isSessionItem(object));

    // correctly constructed
    object[JsonItem::itemTagsKey] = QJsonObject();
    EXPECT_TRUE(converter->isSessionItem(object));
}

//! Checks the validity of json object representing SessionItemTags.

TEST_F(TestJsonItem, isSessionItemTags)
{
    auto converter = createConverter();

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter->isSessionItemTags(object));

    // it also should contain array
    object[JsonItem::defaultTagKey] = "abc";
    object[JsonItem::containerKey] = QJsonArray();
    EXPECT_TRUE(converter->isSessionItemTags(object));
}

//! Checks the validity of json object representing SessionItemContainer.

TEST_F(TestJsonItem, isSessionItemContainer)
{
    auto converter = createConverter();

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter->isSessionItemContainer(object));

    // it also should contain array
    object[JsonItem::tagInfoKey] = QJsonObject();
    object[JsonItem::itemsKey] = QJsonArray();
    EXPECT_TRUE(converter->isSessionItemContainer(object));
}

TEST_F(TestJsonItem, singleItem)
{
    auto converter = createConverter();

    const QString model_type("MultiLayer");

    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    auto child = new SessionItem("Layer");
    parent->insertItem(child, -1);

    auto object = converter->to_json(parent.get());

    // saving to file
    auto fileName = TestUtils::TestFileName(test_dir, "items.json");
    TestUtils::SaveJson(object, fileName);
}

