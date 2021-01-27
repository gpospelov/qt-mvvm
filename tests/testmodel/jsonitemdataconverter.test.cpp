// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonitemdataconverter.h"

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include "mvvm/model/mvvm_types.h"
#include "mvvm/model/sessionitemdata.h"
#include "mvvm/serialization/jsonitemformatassistant.h"
#include <QJsonArray>
#include <QJsonObject>
#include <string>

using namespace ModelView;

//! Test convertion of SessionItemData from/to QJsonObject.

class JsonItemDataConverterTest : public FolderBasedTest {
public:
    JsonItemDataConverterTest() : FolderBasedTest("test_JsonItemData") {}
};

//! Creating QJsonArray from SessionItemData.

TEST_F(JsonItemDataConverterTest, getJson)
{
    JsonItemFormatAssistant assistant;
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
    EXPECT_TRUE(assistant.isSessionItemData(array[0].toObject()));
    EXPECT_TRUE(assistant.isSessionItemData(array[1].toObject()));
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
    for (size_t i = 0; i < roles.size(); ++i)
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
              std::string("identifier2"));
    EXPECT_EQ(data1.data(ItemDataRole::DATA).value<int>(), 43);
    EXPECT_EQ(data1.data(ItemDataRole::TOOLTIP).value<std::string>(), std::string("tooltip1"));
}

//! Checking factory method to create copying converter.
//! It is used normally in the situation, when the item data is fully serialized to JSON, and then
//! desirialized into empty item data.

TEST_F(JsonItemDataConverterTest, createCopyConverter)
{
    auto converter = JsonItemDataConverter::createCopyConverter();

    SessionItemData data;
    data.setData(QVariant::fromValue(std::string("identifier")), ItemDataRole::IDENTIFIER);
    data.setData(42, ItemDataRole::DATA);
    data.setData(QVariant::fromValue(std::string("display")), ItemDataRole::DISPLAY);
    data.setData(QVariant::fromValue(std::string("tooltip")), ItemDataRole::TOOLTIP);

    QJsonArray array = converter->to_json(data);

    SessionItemData data2;
    converter->from_json(array, data2);

    //! Empty data should become the same.
    EXPECT_EQ(data.roles(), data2.roles());
    EXPECT_EQ(data2.data(ItemDataRole::IDENTIFIER).value<std::string>(), "identifier");
    EXPECT_EQ(data2.data(ItemDataRole::DATA).value<int>(), 42);
    EXPECT_EQ(data2.data(ItemDataRole::DISPLAY).value<std::string>(), "display");
    EXPECT_EQ(data2.data(ItemDataRole::TOOLTIP).value<std::string>(), "tooltip");
}

//! Checking factory method for typical scenario for copying whole data while writing, and updating
//! on reading. This is a repetition of previous test.

TEST_F(JsonItemDataConverterTest, createProjectConverter)
{
    auto converter = JsonItemDataConverter::createProjectConverter();

    SessionItemData data;
    data.setData(QVariant::fromValue(std::string("identifier")), ItemDataRole::IDENTIFIER);
    data.setData(42, ItemDataRole::DATA);
    data.setData(QVariant::fromValue(std::string("display")), ItemDataRole::DISPLAY);
    data.setData(QVariant::fromValue(std::string("tooltip")), ItemDataRole::TOOLTIP);
    auto expected_roles = data.roles();

    QJsonArray array = converter->to_json(data);

    // changing data
    data.setData(QVariant::fromValue(std::string("identifier_new")), ItemDataRole::IDENTIFIER);
    data.setData(43, ItemDataRole::DATA);

    // deserializing back
    converter->from_json(array, data);

    //! DATA and IDENTIFIER roles should be as before the serialization
    EXPECT_EQ(data.roles(), expected_roles);
    EXPECT_EQ(data.data(ItemDataRole::IDENTIFIER).value<std::string>(), "identifier");
    EXPECT_EQ(data.data(ItemDataRole::DATA).value<int>(), 42);
    EXPECT_EQ(data.data(ItemDataRole::DISPLAY).value<std::string>(), "display");
    EXPECT_EQ(data.data(ItemDataRole::TOOLTIP).value<std::string>(), "tooltip");
}
