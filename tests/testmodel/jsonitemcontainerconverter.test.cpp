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
#include <QJsonArray>
#include <mvvm/model/mvvm_types.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/serialization/jsonitem_types.h>
#include <mvvm/serialization/jsonitemcontainerconverter.h>
#include <mvvm/serialization/jsonitemdataconverter.h>
#include <mvvm/serialization/jsonitemformatassistant.h>

using namespace ModelView;

//! Checks JsonItemContainerConverter class and its ability to convert SessionItemContainer
//! to json and back. Full testing is not possible since JsonItemContainerConverter
//! requires machinery provided by JsonItemConverter. Simplifed item/json creation is used.

class JsonItemContainerConverterTest : public FolderBasedTest
{
public:
    JsonItemContainerConverterTest()
        : FolderBasedTest("test_JsonItemContainerConverterTest"),
          m_itemdata_converter(std::make_unique<JsonItemDataConverter>())
    {
    }

    std::unique_ptr<JsonItemContainerConverter> createConverter() const
    {
        ConverterContext context;

        //! Toy method to convert SessionItem to JSON object.
        auto to_json = [this](const SessionItem& item) {
            QJsonObject result;
            result[JsonItemFormatAssistant::modelKey] = QString::fromStdString(item.modelType());
//            result[JsonItemFormatAssistant::itemDataKey] = m_itemdata_converter->get_json(item.itemData());
            return result;
        };

        context.m_item_to_json = to_json;

        return std::make_unique<JsonItemContainerConverter>(context);
    }

    ~JsonItemContainerConverterTest();

    std::unique_ptr<JsonItemDataConverterInterface> m_itemdata_converter;
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

    auto converter = createConverter();
    auto json = converter->to_json(container);

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "propertyContainerToFileAndBack.json");
    TestUtils::SaveJson(json, fileName);
}
