// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include <QJsonArray>
#include <QJsonObject>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/sessionitemdata.h>
#include <mvvm/serialization/jsonitemdataconverter.h>
#include <mvvm/serialization/jsonvariantconverter.h>
#include <string>

using namespace ModelView;

//! Test convertion of SessionItemData from/to QJsonObject.

class JsonItemDataConverterTest : public FolderBasedTest
{
public:
    JsonItemDataConverterTest() : FolderBasedTest("test_JsonItemData") {}
    ~JsonItemDataConverterTest();
};

JsonItemDataConverterTest::~JsonItemDataConverterTest() = default;

//! Checks if json object is correctly identified as representing DataRole.

TEST_F(JsonItemDataConverterTest, isValidDataRole)
{
    JsonItemDataConverter converter;
    JsonVariantConverter variant_converter;

    // valid json object representing DataRole
    QJsonObject object;
    object[JsonItemDataConverter::roleKey] = 42;
    object[JsonItemDataConverter::variantKey] = variant_converter.get_json(QVariant(1.23));
    EXPECT_TRUE(converter.is_item_data(object));

    // invalid json object which can't represent DataRole
    QJsonObject object2;
    object2[JsonItemDataConverter::roleKey] = 42;
    EXPECT_FALSE(converter.is_item_data(object2));

    // another invalid json object
    QJsonObject object3;
    object3[JsonItemDataConverter::roleKey] = 42;
    object3[JsonItemDataConverter::variantKey] = variant_converter.get_json(QVariant(1.23));
    object3["abc"] = variant_converter.get_json(QVariant::fromValue(std::string("xxx")));
    EXPECT_FALSE(converter.is_item_data(object3));
}

//! Creating QJsonArray from SessionItemData.

TEST_F(JsonItemDataConverterTest, getJson)
{
    JsonItemDataConverter converter;

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

TEST_F(JsonItemDataConverterTest, fromItemToJsonAndBack)
{
    JsonItemDataConverter converter;

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
    auto fileName = TestUtils::TestFileName(testDir(), "itemdata.json");
    TestUtils::SaveJson(array, fileName);

    // constructing data from json array
    SessionItemData data2;
    converter.from_json(array, data2);
    EXPECT_EQ(data2.roles().size(), 3u);

    EXPECT_EQ(data2.roles(), roles);
    for (auto role : roles) {
        EXPECT_EQ(data2.data(role), expected[role - 1]);
    }
}

//! Filtering certain roles while writing to json.

TEST_F(JsonItemDataConverterTest, filteredRoles)
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
    JsonItemDataConverter converter;
    converter.set_role_filter({1, 3});
    QJsonArray array = converter.get_json(data);

    // constructing data from json array
    SessionItemData data2;
    converter.from_json(array, data2);
    EXPECT_EQ(data2.roles().size(), 1u);
    EXPECT_EQ(data2.data(2).value<double>(), 1.23);
}

//! By default tooltip role is filtered out.

TEST_F(JsonItemDataConverterTest, tooltipRole)
{
    // initial data
    SessionItemData data;
    data.setData(QVariant::fromValue(std::string("tooltip")), ItemDataRole::TOOLTIP);

    // constructing json array from data
    JsonItemDataConverter converter;
    QJsonArray array = converter.get_json(data);

    // constructing data from json array
    SessionItemData data2;
    converter.from_json(array, data2);
    EXPECT_EQ(data2.roles().size(), 0u);
}

//! Update SessionItemData from json obtained from another JsonItemData.

TEST_F(JsonItemDataConverterTest, updateFromJson)
{
    const std::vector<int> roles = {ItemDataRole::IDENTIFIER, ItemDataRole::DATA,
                                    ItemDataRole::TOOLTIP};
    const std::vector<QVariant> variants = {QVariant::fromValue(std::string("identifier1")),
                                            QVariant::fromValue(42),
                                            QVariant::fromValue(std::string("tooltip1"))};

    // initial data
    SessionItemData data1;
    for (size_t i=0; i<roles.size(); ++i)
        data1.setData(variants[i], roles[i]);

    // data intended for serialization
    SessionItemData data2;
    data1.setData(QVariant::fromValue(43), ItemDataRole::DATA);
    data1.setData(QVariant::fromValue(std::string("identifier2")), ItemDataRole::IDENTIFIER);

    // constructing json array from data
    JsonItemDataConverter converter;
    QJsonArray array = converter.get_json(data2);

    // updating data1 from json array
    converter.from_json(array, data1);

    // roles as in initial object, id+data as in data2, tooltip as in data1
    EXPECT_EQ(data1.roles(), roles);
    EXPECT_EQ(data1.data(ItemDataRole::IDENTIFIER).value<std::string>(), std::string("identifier2"));
    EXPECT_EQ(data1.data(ItemDataRole::DATA).value<int>(), 43);
    EXPECT_EQ(data1.data(ItemDataRole::TOOLTIP).value<std::string>(), std::string("tooltip1"));
}
