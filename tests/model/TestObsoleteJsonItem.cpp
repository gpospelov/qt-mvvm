#include "google_test.h"
#include "sessionmodel.h"
#include "obsoletejsonitem.h"
#include "sessionitem.h"
#include "test_utils.h"
#include "taginfo.h"
#include <QJsonObject>
#include <QJsonArray>

using namespace ModelView;

//! Checks JsonItem class and its ability to convert SessionItems to json and back.

class TestObsoleteJsonItem : public ::testing::Test
{
public:
    ~TestObsoleteJsonItem();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }
};

TestObsoleteJsonItem::~TestObsoleteJsonItem() = default;
const QString TestObsoleteJsonItem::test_dir = "test_JsonModel";

//! Checks the validity of json object representing item tree.

TEST_F(TestObsoleteJsonItem, isValidItem)
{
    ObsoleteJsonItem converter;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(converter.is_item(object));

    // it also should contain array
    object[ObsoleteJsonItem::modelKey] = "abc";
    object[ObsoleteJsonItem::parentTagKey] = "tag";
    object[ObsoleteJsonItem::itemsKey] = 42; // incorrect
    object[ObsoleteJsonItem::itemDataKey] = QJsonArray();
    object[ObsoleteJsonItem::itemTagsKey] = QJsonArray();
    EXPECT_FALSE(converter.is_item(object));

    // correctly constructed
    object[ObsoleteJsonItem::itemsKey] = QJsonArray();
    object[ObsoleteJsonItem::itemDataKey] = QJsonArray();
    object[ObsoleteJsonItem::itemTagsKey] = QJsonArray();
    EXPECT_TRUE(converter.is_item(object));

    // wrong extra key in json
    object["abc"] = "abc";
    EXPECT_FALSE(converter.is_item(object));
    EXPECT_FALSE(converter.is_item(object));
}

//! Checks creation of json object: single item (no children) without the data.

TEST_F(TestObsoleteJsonItem, singleItem)
{
    const QString model_type("MultiLayer");

    ObsoleteJsonItem converter;
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));

    QJsonObject object;
    converter.item_to_json(parent.get(), object);

    EXPECT_EQ(object[ObsoleteJsonItem::modelKey], model_type);
    EXPECT_EQ(object[ObsoleteJsonItem::itemsKey].toArray().size(), 0);
    EXPECT_EQ(object[ObsoleteJsonItem::itemDataKey].toArray().size(), 1); // item identifier
}

//! Checks creation of json object: parent item with one data variant and one child on board.

TEST_F(TestObsoleteJsonItem, parentAndChild)
{
    const QString model_type("MultiLayer");
    ObsoleteJsonItem converter;

    // constructing multilayer
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    parent->setData(QVariant::fromValue(42), 1);
    auto child = new SessionItem("Layer");
    parent->insertItem(child, -1);

    QJsonObject object;
    converter.item_to_json(parent.get(), object);

    EXPECT_EQ(object[ObsoleteJsonItem::modelKey], model_type);
    EXPECT_EQ(object[ObsoleteJsonItem::itemsKey].toArray().size(), 1);
    EXPECT_EQ(object[ObsoleteJsonItem::itemDataKey].toArray().size(), 3);

    // saving to file
    auto fileName = TestUtils::TestFileName(test_dir, "items.json");
    TestUtils::SaveJson(object, fileName);
}
