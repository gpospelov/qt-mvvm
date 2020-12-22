// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsontaginfoconverter.h"

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include "mvvm/model/taginfo.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>

using namespace ModelView;

//! Test convertion of TagInfo from/to QJsonObject.

class JsonTagInfoConverterTest : public FolderBasedTest {
public:
    JsonTagInfoConverterTest() : FolderBasedTest("test_JsonTagInfoConverter") {}
};

//! Checks if json object is correctly identified as representing TagInfo.

TEST_F(JsonTagInfoConverterTest, isItemTag)
{
    JsonTagInfoConverter converter;

    // valid json object representing DataRole
    QJsonObject object;
    object[JsonTagInfoConverter::nameKey] = QString::fromStdString("tag1");
    object[JsonTagInfoConverter::minKey] = 0;
    object[JsonTagInfoConverter::maxKey] = 1;
    object[JsonTagInfoConverter::modelsKey] = QJsonArray();

    EXPECT_TRUE(converter.isTagInfo(object));

    // invalid (not fully constructed) json object which can't represent TagInfo
    QJsonObject object2;
    object2[JsonTagInfoConverter::minKey] = 42;
    EXPECT_FALSE(converter.isTagInfo(object2));
}

//! Creating QJsonArray from TagInfo.

TEST_F(JsonTagInfoConverterTest, toJson)
{
    JsonTagInfoConverter converter;

    TagInfo tag("tag1", 0, -1, std::vector<std::string>() = {});
    auto object = converter.to_json(tag);

    // this object represents TagInfo
    EXPECT_TRUE(converter.isTagInfo(object));
}

//! From TagInfo to json and back.

TEST_F(JsonTagInfoConverterTest, tagInfoToJsonAndBack)
{
    JsonTagInfoConverter converter;

    TagInfo tag("tag", 0, 42, std::vector<std::string>() = {"aaa", "bbb"});
    auto object = converter.to_json(tag);

    TagInfo reco_tag = converter.from_json(object);

    EXPECT_EQ(reco_tag.name(), tag.name());
    EXPECT_EQ(reco_tag.min(), tag.min());
    EXPECT_EQ(reco_tag.max(), tag.max());
    EXPECT_EQ(reco_tag.modelTypes(), tag.modelTypes());
}

//! To file and back.

TEST_F(JsonTagInfoConverterTest, tagInfoToFileAndBack)
{
    const std::string tag_name("tag");
    const std::string model_type("model");
    JsonTagInfoConverter converter;

    TagInfo tag = TagInfo::propertyTag(tag_name, model_type);
    auto object = converter.to_json(tag);

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "taginfo.json");
    TestUtils::SaveJson(object, fileName);

    auto document = TestUtils::LoadJson(fileName);
    TagInfo reco_tag = converter.from_json(document.object());

    EXPECT_EQ(reco_tag.name(), tag_name);
    EXPECT_EQ(reco_tag.min(), 1);
    EXPECT_EQ(reco_tag.max(), 1);
    EXPECT_EQ(reco_tag.modelTypes(), std::vector<std::string>() = {model_type});
}
