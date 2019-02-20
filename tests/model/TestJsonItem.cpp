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
    ~TestJsonItem();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }
};

TestJsonItem::~TestJsonItem() = default;
const QString TestJsonItem::test_dir = "test_JsonModel";

//! Checks the validity of json object representing item tree.

TEST_F(TestJsonItem, isValidItem)
{
    JsonItem converter;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter.is_item(object));

    // it also should contain array
    object[JsonItem::modelKey] = "abc";
    object[JsonItem::parentTagKey] = "tag";
    object[JsonItem::itemsKey] = 42; // incorrect
    object[JsonItem::itemDataKey] = QJsonArray();
    object[JsonItem::itemTagsKey] = QJsonArray();
    EXPECT_FALSE(converter.is_item(object));

    // correctly constructed
    object[JsonItem::itemsKey] = QJsonArray();
    object[JsonItem::itemDataKey] = QJsonArray();
    object[JsonItem::itemTagsKey] = QJsonArray();
    EXPECT_TRUE(converter.is_item(object));

    // wrong extra key in json
    object["abc"] = "abc";
    EXPECT_FALSE(converter.is_item(object));
    EXPECT_FALSE(converter.is_item(object));
}

//! Checks creation of json object: single item (no children) without the data.

TEST_F(TestJsonItem, singleItem)
{
    const QString model_type("MultiLayer");

    JsonItem converter;
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));

    QJsonObject object;
    converter.item_to_json(parent.get(), object);

    EXPECT_EQ(object[JsonItem::modelKey], model_type);
    EXPECT_EQ(object[JsonItem::itemsKey].toArray().size(), 0);
    EXPECT_EQ(object[JsonItem::itemDataKey].toArray().size(), 1); // item identifier
}

//! Checks creation of json object: parent item with one data variant and one child on board.

TEST_F(TestJsonItem, parentAndChild)
{
    const QString model_type("MultiLayer");
    JsonItem converter;

    // constructing multilayer
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    parent->setData(QVariant::fromValue(42), 1);
    auto child = new SessionItem("Layer");
    parent->insertItem(child, -1);

    QJsonObject object;
    converter.item_to_json(parent.get(), object);

    EXPECT_EQ(object[JsonItem::modelKey], model_type);
    EXPECT_EQ(object[JsonItem::itemsKey].toArray().size(), 1);
    EXPECT_EQ(object[JsonItem::itemDataKey].toArray().size(), 3);

    // saving to file
    auto fileName = TestUtils::TestFileName(test_dir, "items.json");
    TestUtils::SaveJson(object, fileName);
}
