#include <gtest/gtest.h>
#include "sessionmodel.h"
#include "jsonmodel.h"
#include "sessionitem.h"
#include "test_utils.h"
#include <QJsonObject>
#include <QJsonArray>

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

//! Check single item (no children) without the data.

TEST_F(TestJsonModel, singleItem)
{
    const QString model_type("MultiLayer");

    JsonModel converter;
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));

    QJsonObject object;
    converter.write(parent.get(), object);

    EXPECT_EQ(object[JsonModel::modelKey], model_type);
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 0);
    EXPECT_EQ(object[JsonModel::itemDataKey].toArray().size(), 0);
}

//! Parent item with one data variant and one child on board.

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
    converter.write(parent.get(), object);

    EXPECT_EQ(object[JsonModel::modelKey], model_type);
    EXPECT_EQ(object[JsonModel::itemsKey].toArray().size(), 1);
    EXPECT_EQ(object[JsonModel::itemDataKey].toArray().size(), 1);

    // saving to file
    auto fileName = TestUtils::TestFileName(test_dir, "model.json");
    TestUtils::SaveJson(object, fileName);
}
