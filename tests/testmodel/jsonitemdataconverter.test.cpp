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
#include <mvvm/serialization/jsonitemformatassistant.h>
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
    object[JsonItemFormatAssistant::roleKey] = 42;
    object[JsonItemFormatAssistant::variantKey] = variant_converter.get_json(QVariant(1.23));
    EXPECT_TRUE(converter.is_item_data(object));

    // invalid json object which can't represent DataRole
    QJsonObject object2;
    object2[JsonItemFormatAssistant::roleKey] = 42;
    EXPECT_FALSE(converter.is_item_data(object2));

    // another invalid json object
    QJsonObject object3;
    object3[JsonItemFormatAssistant::roleKey] = 42;
    object3[JsonItemFormatAssistant::variantKey] = variant_converter.get_json(QVariant(1.23));
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
    QJsonArray array = converter.to_json(data);

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
    QJsonArray array = converter.to_json(data);
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

//! By default tooltip role is enabled for read and write.

TEST_F(JsonItemDataConverterTest, tooltipRole)
{
    // initial data
    SessionItemData data;
    data.setData(QVariant::fromValue(std::string("tooltip")), ItemDataRole::TOOLTIP);

    // constructing json array from data
    JsonItemDataConverter converter;
    QJsonArray array = converter.to_json(data);

    // constructing data from json array
    SessionItemData data2;
    converter.from_json(array, data2);
    EXPECT_EQ(data2.roles().size(), 1u);
    EXPECT_EQ(data2.data(ItemDataRole::TOOLTIP).value<std::string>(), "tooltip");
}

//! Write filtered roles, read all into empty SessionItemData.

TEST_F(JsonItemDataConverterTest, writeFilteredReadAll)
{
    // initial data
    SessionItemData data;
    data.setData(QVariant::fromValue(std::string("abc")), ItemDataRole::IDENTIFIER);
    data.setData(42, ItemDataRole::DATA);
    data.setData(QVariant::fromValue(std::string("abc")), ItemDataRole::DISPLAY);
    data.setData(QVariant::fromValue(std::string("tooltip")), ItemDataRole::TOOLTIP);

    // constructing json array from data
    auto to_json_accept = [](auto role) { return role != ItemDataRole::TOOLTIP; };

    JsonItemDataConverter converter(to_json_accept, {});
    QJsonArray array = converter.to_json(data);

    // constructing data from json array
    SessionItemData data2;
    converter.from_json(array, data2);
    EXPECT_EQ(data2.roles().size(), 3u);
    EXPECT_FALSE(data2.hasData(ItemDataRole::TOOLTIP));
}

//! Write all roles, read filtered into empty SessionItemData.

TEST_F(JsonItemDataConverterTest, writeAllReadFiltered)
{
    // initial data
    SessionItemData data;
    data.setData(QVariant::fromValue(std::string("abc")), ItemDataRole::IDENTIFIER);
    data.setData(42, ItemDataRole::DATA);
    data.setData(QVariant::fromValue(std::string("abc")), ItemDataRole::DISPLAY);
    data.setData(QVariant::fromValue(std::string("tooltip")), ItemDataRole::TOOLTIP);

    // constructing json array from data
    auto from_json_accept = [](auto role) { return role == ItemDataRole::TOOLTIP; };

    JsonItemDataConverter converter({}, from_json_accept);
    QJsonArray array = converter.to_json(data);

    // constructing data from json array
    SessionItemData data2;
    converter.from_json(array, data2);

    // while array itself has 4 elements, restored data has only TOOLTIPS as defined in filter
    EXPECT_EQ(array.size(), 4u);
    EXPECT_EQ(data2.roles().size(), 1u);
    EXPECT_TRUE(data2.hasData(ItemDataRole::TOOLTIP));
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
    QJsonArray array = converter.to_json(data2);

    // updating data1 from json array
    converter.from_json(array, data1);

    // roles as in initial object, id+data as in data2, tooltip as in data1
    EXPECT_EQ(data1.roles(), roles);
    EXPECT_EQ(data1.data(ItemDataRole::IDENTIFIER).value<std::string>(),
    std::string("identifier2")); EXPECT_EQ(data1.data(ItemDataRole::DATA).value<int>(), 43);
    EXPECT_EQ(data1.data(ItemDataRole::TOOLTIP).value<std::string>(), std::string("tooltip1"));
}
