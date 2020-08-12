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
#include <QJsonObject>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/serialization/jsonitemcontainerconverter.h>
#include <mvvm/serialization/jsonitemformatassistant.h>

using namespace ModelView;

//! Checks JsonItemContainerConverter class and its ability to convert SessionItemContainer
//! to json and back. Full testing is not possible since JsonItemContainerConverter
//! requires machinery provided by JsonItemConverter. Simplifed item/json creation is used.

class JsonItemContainerConverterTest : public FolderBasedTest
{
public:
    JsonItemContainerConverterTest() : FolderBasedTest("test_JsonItemContainerConverterTest") {}

    std::unique_ptr<JsonItemContainerConverter> createConverter() const { return {}; }

    ~JsonItemContainerConverterTest();
};

JsonItemContainerConverterTest::~JsonItemContainerConverterTest() = default;

//! PropertyItem to json object.

TEST_F(JsonItemContainerConverterTest, propertyContainerToJson)
{
    TagInfo tag = TagInfo::propertyTag("thickness", Constants::PropertyType);
    SessionItemContainer container(tag);
    EXPECT_TRUE(container.insertItem(new PropertyItem, 0));

    JsonItemContainerConverter converter;
    auto json = converter.to_json(container);

    JsonItemFormatAssistant assistant;
    EXPECT_TRUE(assistant.isSessionItemContainer(json));
}

TEST_F(JsonItemContainerConverterTest, propertyContainerToFile)
{
    TagInfo tag = TagInfo::propertyTag("thickness", Constants::PropertyType);
    SessionItemContainer container(tag);
    EXPECT_TRUE(container.insertItem(new PropertyItem, 0));

    JsonItemContainerConverter converter;
    auto json = converter.to_json(container);

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "propertyContainerToFileAndBack.json");
    TestUtils::SaveJson(json, fileName);
}
