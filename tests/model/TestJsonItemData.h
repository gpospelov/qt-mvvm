#include <gtest/gtest.h>
#include "jsonitemdata.h"
#include "test_utils.h"
#include "jsonvariant.h"
#include <QJsonObject>
#include <string>
#include <QDebug>

//! Test convertion of SessionItemData from/to QJsonObject.

class TestJsonItemData : public ::testing::Test
{
public:
    ~TestJsonItemData();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }
};

const QString TestJsonItemData::test_dir = "test_JsonItemData";

TestJsonItemData::~TestJsonItemData() = default;

//! Checks if json object is correctly identified as representing DataRole.

TEST_F(TestJsonItemData, isValidDataRole)
{
    // valid json object representing DataRole
    QJsonObject object;
    object[JsonItemData::roleKey] = 42;
    object[JsonItemData::variantKey] = json::get_json(QVariant(1.23));
    EXPECT_TRUE(JsonItemData::is_valid(object));

    // invalid json object which can't represent DataRole
    QJsonObject object2;
    object2[JsonItemData::roleKey] = 42;
    EXPECT_FALSE(JsonItemData::is_valid(object2));

    // another invalid json object
    QJsonObject object3;
    object3[JsonItemData::roleKey] = 42;
    object3[JsonItemData::variantKey] = json::get_json(QVariant(1.23));
    object3["abc"] = json::get_json(QVariant::fromValue(std::string("xxx")));
    EXPECT_FALSE(JsonItemData::is_valid(object3));
}

//! Creating QJsonArray from SessionItemData.

TEST_F(TestJsonItemData, getJson)
{
    // construction SessionItem data
    SessionItemData data;
    const int role = Qt::UserRole + 1;
    data.setData(QVariant::fromValue(42), role);
    data.setData(QVariant::fromValue(std::string("abc")), role+2);

    // creating json object out of it
    QJsonArray array = JsonItemData::get_json(data);

    // it should contain two json objects
    EXPECT_EQ(array.size(), 2);
    EXPECT_TRUE(array[0].isObject());
    EXPECT_TRUE(array[1].isObject());

    // and these objects repesent DataRole
    EXPECT_TRUE(JsonItemData::is_valid(array[0].toObject()));
    EXPECT_TRUE(JsonItemData::is_valid(array[1].toObject()));
}

TEST_F(TestJsonItemData, thereAndBack)
{
    // initial data
    const std::vector<int> roles = {1, 2, 3};
    const std::vector<QVariant> variants = {
        QVariant::fromValue(42), QVariant::fromValue(1.23), QVariant::fromValue(std::string("abc"))
    };

    // constructing SessionItemData
    SessionItemData data;
    for (size_t i=0; i<roles.size(); ++i)
        data.setData(variants[i], roles[i]);

    // constructing json array from data
    QJsonArray array = JsonItemData::get_json(data);
    auto fileName = TestUtils::TestFileName(test_dir, "itemdata.json");
    TestUtils::SaveJson(array, fileName);

    // constructing data from json array
    auto data2 = JsonItemData::get_data(array);
    EXPECT_EQ(data2.roles().size(), 3u);

    EXPECT_EQ(data2.roles(), roles);
    for (auto role : roles) {
        EXPECT_EQ(data2.data(role), variants[role-1]);
    }

}
