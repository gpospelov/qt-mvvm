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
#include <QJsonObject>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/serialization/jsonitemdata.h>
#include <mvvm/serialization/jsonvariant.h>
#include <string>

using namespace ModelView;

//! Test convertion of SessionItemData from/to QJsonObject.

class JsonItemDataTest : public ::testing::Test
{
public:
    ~JsonItemDataTest();

    static inline const QString test_dir = "test_JsonItemData";

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }
};

JsonItemDataTest::~JsonItemDataTest() = default;

//! Checks if json object is correctly identified as representing DataRole.

TEST_F(JsonItemDataTest, isValidDataRole)
{
    JsonItemData converter;
    JsonVariant variant_converter;

    // valid json object representing DataRole
    QJsonObject object;
    object[JsonItemData::roleKey] = 42;
    object[JsonItemData::variantKey] = variant_converter.get_json(QVariant(1.23));
    EXPECT_TRUE(converter.is_item_data(object));

    // invalid json object which can't represent DataRole
    QJsonObject object2;
    object2[JsonItemData::roleKey] = 42;
    EXPECT_FALSE(converter.is_item_data(object2));

    // another invalid json object
    QJsonObject object3;
    object3[JsonItemData::roleKey] = 42;
    object3[JsonItemData::variantKey] = variant_converter.get_json(QVariant(1.23));
    object3["abc"] = variant_converter.get_json(QVariant::fromValue(std::string("xxx")));
    EXPECT_FALSE(converter.is_item_data(object3));
}

//! Creating QJsonArray from SessionItemData.

TEST_F(JsonItemDataTest, getJson)
{
    JsonItemData converter;

    // construction SessionItem data
    SessionItemData data;
    const int role = Qt::UserRole + 1;
    data.setData(QVariant::fromValue(42), role);
    data.setData(QVariant::fromValue(std::string("abc")), role + 2);

    // creating json object out of it
    QJsonArray array = converter.get_json(data);

    // it should contain two json objects
    EXPECT_EQ(array.size(), 2);
    EXPECT_TRUE(array[0].isObject());
    EXPECT_TRUE(array[1].isObject());

    // and these objects repesent DataRole
    EXPECT_TRUE(converter.is_item_data(array[0].toObject()));
    EXPECT_TRUE(converter.is_item_data(array[1].toObject()));
}

//! From SessionItemData to json and back.

TEST_F(JsonItemDataTest, fromItemToJsonAndBack)
{
    JsonItemData converter;

    // initial data
    const std::vector<int> roles = {1, 2, 3};
    const std::vector<QVariant> expected = {QVariant::fromValue(42), QVariant::fromValue(1.23),
                                            QVariant::fromValue(std::string("abc"))};

    // constructing SessionItemData
    SessionItemData data;
    for (size_t i = 0; i < roles.size(); ++i)
        data.setData(expected[i], roles[i]);

    // constructing json array from data
    QJsonArray array = converter.get_json(data);
    auto fileName = TestUtils::TestFileName(test_dir, "itemdata.json");
    TestUtils::SaveJson(array, fileName);

    // constructing data from json array
    auto data2 = converter.get_data(array);
    EXPECT_EQ(data2->roles().size(), 3u);

    EXPECT_EQ(data2->roles(), roles);
    for (auto role : roles) {
        EXPECT_EQ(data2->data(role), expected[role - 1]);
    }
}

//! Filtering certain roles while writing to json.

TEST_F(JsonItemDataTest, filteredRoles)
{
    // initial data
    const std::vector<int> roles = {1, 2, 3};
    const std::vector<QVariant> variants = {QVariant::fromValue(42), QVariant::fromValue(1.23),
                                            QVariant::fromValue(std::string("abc"))};

    // constructing SessionItemData
    SessionItemData data;
    for (size_t i = 0; i < roles.size(); ++i)
        data.setData(variants[i], roles[i]);

    // constructing json array from data
    JsonItemData converter;
    converter.set_role_filter({1, 3});
    QJsonArray array = converter.get_json(data);

    // constructing data from json array
    auto data2 = converter.get_data(array);
    EXPECT_EQ(data2->roles().size(), 1u);
    EXPECT_EQ(data2->data(2).value<double>(), 1.23);
}
