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
#include <QJsonDocument>
#include <QJsonObject>
#include <mvvm/model/taginfo.h>
#include <mvvm/serialization/jsontaginfo.h>
#include <string>

using namespace ModelView;

//! Test convertion of SessionItemData from/to QJsonObject.

class JsonTagInfoTest : public ::testing::Test
{
public:
    ~JsonTagInfoTest();

    static const QString test_dir;

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }
};

const QString JsonTagInfoTest::test_dir = "test_JsonTagInfo";

JsonTagInfoTest::~JsonTagInfoTest() = default;

//! Checks if json object is correctly identified as representing TagInfo.

TEST_F(JsonTagInfoTest, isItemTag)
{
    JsonTagInfo converter;

    // valid json object representing DataRole
    QJsonObject object;
    object[JsonTagInfo::nameKey] = QString::fromStdString("tag1");
    object[JsonTagInfo::minKey] = 0;
    object[JsonTagInfo::maxKey] = 1;
    object[JsonTagInfo::modelsKey] = QJsonArray();

    EXPECT_TRUE(converter.isTagInfo(object));

    // invalid (not fully constructed) json object which can't represent TagInfo
    QJsonObject object2;
    object2[JsonTagInfo::minKey] = 42;
    EXPECT_FALSE(converter.isTagInfo(object2));
}

//! Creating QJsonArray from TagInfo.

TEST_F(JsonTagInfoTest, toJson)
{
    JsonTagInfo converter;

    TagInfo tag("tag1", 0, -1, std::vector<std::string>() = {});
    auto object = converter.to_json(tag);

    // this object represents TagInfo
    EXPECT_TRUE(converter.isTagInfo(object));
}

//! From TagInfo to json and back.

TEST_F(JsonTagInfoTest, tagInfoToJsonAndBack)
{
    JsonTagInfo converter;

    TagInfo tag("tag", 0, 42, std::vector<std::string>() = {"aaa", "bbb"});
    auto object = converter.to_json(tag);

    TagInfo reco_tag = converter.from_json(object);

    EXPECT_EQ(reco_tag.name(), tag.name());
    EXPECT_EQ(reco_tag.min(), tag.min());
    EXPECT_EQ(reco_tag.max(), tag.max());
    EXPECT_EQ(reco_tag.modelTypes(), tag.modelTypes());
}

//! To file and back.

TEST_F(JsonTagInfoTest, tagInfoToFileAndBack)
{
    const std::string tag_name("tag");
    const std::string model_type("model");
    JsonTagInfo converter;

    TagInfo tag = TagInfo::propertyTag(tag_name, model_type);
    auto object = converter.to_json(tag);

    // saving object to file
    auto fileName = TestUtils::TestFileName(test_dir, "taginfo.json");
    TestUtils::SaveJson(object, fileName);

    auto document = TestUtils::LoadJson(fileName);
    TagInfo reco_tag = converter.from_json(document.object());

    EXPECT_EQ(reco_tag.name(), tag_name);
    EXPECT_EQ(reco_tag.min(), 1);
    EXPECT_EQ(reco_tag.max(), 1);
    EXPECT_EQ(reco_tag.modelTypes(), std::vector<std::string>() = {model_type});
}
