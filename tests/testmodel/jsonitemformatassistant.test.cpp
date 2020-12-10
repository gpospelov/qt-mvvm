// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <QJsonArray>
#include <QJsonObject>
#include <mvvm/serialization/jsonitemformatassistant.h>
#include <mvvm/serialization/jsonvariantconverter.h>

using namespace ModelView;

//! Checks JsonItem class and its ability to convert SessionItems to json and back.

class JsonItemFormatAssistantTest : public ::testing::Test
{
public:
    ~JsonItemFormatAssistantTest();
};

JsonItemFormatAssistantTest::~JsonItemFormatAssistantTest() = default;

//! Checks the validity of json object representing SessionItem.

TEST_F(JsonItemFormatAssistantTest, isSessionItem)
{
    JsonItemFormatAssistant assistant;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(assistant.isSessionItem(object));

    // it also should contain array
    object[JsonItemFormatAssistant::modelKey] = "abc";
    object[JsonItemFormatAssistant::itemDataKey] = QJsonArray();
    object[JsonItemFormatAssistant::itemTagsKey] = 42; // intentionally incorrect
    EXPECT_FALSE(assistant.isSessionItem(object));

    // correctly constructed
    object[JsonItemFormatAssistant::itemTagsKey] = QJsonObject();
    EXPECT_TRUE(assistant.isSessionItem(object));
}

//! Checks if json object is correctly identified as representing DataRole.

TEST_F(JsonItemFormatAssistantTest, isValidDataRole)
{
    JsonItemFormatAssistant assistant;
    JsonVariantConverter variant_converter;

    // valid json object representing DataRole
    QJsonObject object;
    object[JsonItemFormatAssistant::roleKey] = 42;
    object[JsonItemFormatAssistant::variantKey] = variant_converter.get_json(QVariant(1.23));
    EXPECT_TRUE(assistant.isSessionItemData(object));

    // invalid json object which can't represent DataRole
    QJsonObject object2;
    object2[JsonItemFormatAssistant::roleKey] = 42;
    EXPECT_FALSE(assistant.isSessionItemData(object2));

    // another invalid json object
    QJsonObject object3;
    object3[JsonItemFormatAssistant::roleKey] = 42;
    object3[JsonItemFormatAssistant::variantKey] = variant_converter.get_json(QVariant(1.23));
    object3["abc"] = variant_converter.get_json(QVariant::fromValue(std::string("xxx")));
    EXPECT_FALSE(assistant.isSessionItemData(object3));
}

//! Checks the validity of json object representing SessionItemTags.

TEST_F(JsonItemFormatAssistantTest, isSessionItemTags)
{
    JsonItemFormatAssistant assistant;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(assistant.isSessionItemTags(object));

    // it also should contain array
    object[JsonItemFormatAssistant::defaultTagKey] = "abc";
    object[JsonItemFormatAssistant::containerKey] = QJsonArray();
    EXPECT_TRUE(assistant.isSessionItemTags(object));
}

//! Checks the validity of json object representing SessionItemContainer.

TEST_F(JsonItemFormatAssistantTest, isSessionItemContainer)
{
    JsonItemFormatAssistant assistant;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(assistant.isSessionItemContainer(object));

    // it also should contain array
    object[JsonItemFormatAssistant::tagInfoKey] = QJsonObject();
    object[JsonItemFormatAssistant::itemsKey] = QJsonArray();
    EXPECT_TRUE(assistant.isSessionItemContainer(object));
}

//! Validity of json object representing SessionModel.

TEST_F(JsonItemFormatAssistantTest, isValidSessionModel)
{
    JsonItemFormatAssistant assistant;

    // empty json object is not valid
    QJsonObject object;
    EXPECT_FALSE(assistant.isSessionModel(object));

    // json object representing valid SessionModel
    QJsonObject object2;
    object2[JsonItemFormatAssistant::sessionModelKey] = "abc";
    object2[JsonItemFormatAssistant::itemsKey] = QJsonArray();
    EXPECT_TRUE(assistant.isSessionModel(object2));
}
