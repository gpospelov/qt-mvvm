// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonitemcontainerconverter.h"

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include "mvvm/model/mvvm_types.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitemcontainer.h"
#include "mvvm/serialization/jsonitem_types.h"
#include "mvvm/serialization/jsonitemdataconverter.h"
#include "mvvm/serialization/jsonitemformatassistant.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace ModelView;

//! Checks JsonItemContainerConverter class and its ability to convert SessionItemContainer
//! to json and back. Full testing is not possible since JsonItemContainerConverter
//! requires machinery provided by JsonItemConverter. Simplifed item/json creation is used.

class JsonItemContainerConverterTest : public FolderBasedTest {
public:
    JsonItemContainerConverterTest()
        : FolderBasedTest("test_JsonItemContainerConverterTest")
        , m_itemdata_converter(std::make_unique<JsonItemDataConverter>())
    {
    }

    std::unique_ptr<JsonItemContainerConverter> createConverter() const
    {
        //! Simplified method to convert SessionItem to JSON object.
        auto to_json = [this](const SessionItem& item) {
            QJsonObject result;
            result[JsonItemFormatAssistant::modelKey] = QString::fromStdString(item.modelType());
            result[JsonItemFormatAssistant::itemDataKey] =
                m_itemdata_converter->to_json(*item.itemData());
            result[JsonItemFormatAssistant::itemTagsKey] = QJsonObject();
            return result;
        };

        //! Simplified method to create SessionItem from JSON object
        auto create_item = [this](const QJsonObject& json) {
            auto result = std::make_unique<SessionItem>();
            m_itemdata_converter->from_json(json[JsonItemFormatAssistant::itemDataKey].toArray(),
                                            *result->itemData());
            return result;
        };

        //! Simplified method to update SessionItem from JSON object
        auto update_item = [this](const QJsonObject& json, SessionItem* item) {
            m_itemdata_converter->from_json(json[JsonItemFormatAssistant::itemDataKey].toArray(),
                                            *item->itemData());
        };

        ConverterCallbacks callbacks{to_json, create_item, update_item};
        return std::make_unique<JsonItemContainerConverter>(callbacks);
    }

    std::unique_ptr<JsonItemDataConverter> m_itemdata_converter;
};

//! SessionItemContainer (with single property item) to json object.

TEST_F(JsonItemContainerConverterTest, propertyContainerToJson)
{
    // creating container
    TagInfo tag = TagInfo::propertyTag("thickness", Constants::PropertyType);
    SessionItemContainer container(tag);

    // inserting single property item
    auto item = new PropertyItem;
    item->setData(42);
    EXPECT_TRUE(container.insertItem(item, 0));

    // converting top JSON and checking that it is valid JSON object
    auto converter = createConverter();
    auto json = converter->to_json(container);

    JsonItemFormatAssistant assistant;
    EXPECT_TRUE(assistant.isSessionItemContainer(json));
}

//! SessionItemContainer (with single property item) to json object and back.

TEST_F(JsonItemContainerConverterTest, propertyContainerToJsonAndBack)
{
    // creating container
    TagInfo tag = TagInfo::propertyTag("thickness", Constants::PropertyType);
    SessionItemContainer container(tag);

    // inserting single property item
    auto item = new PropertyItem;
    item->setData(42);
    EXPECT_TRUE(container.insertItem(item, 0));

    // converting top JSON
    auto converter = createConverter();
    auto json = converter->to_json(container);

    // creating second container with same layout, and updating it from JSON
    SessionItemContainer container2(tag);
    auto item2 = new PropertyItem;
    item2->setData(43);
    EXPECT_TRUE(container2.insertItem(item2, 0));
    converter->from_json(json, container2);

    // Checking that item in container2 has been reused, and get same properties as item.
    EXPECT_EQ(container2.itemAt(0), item2);
    EXPECT_EQ(item->displayName(), item2->displayName());
    EXPECT_EQ(item->identifier(), item2->identifier());
    EXPECT_EQ(42, item2->data<int>());
}

//! SessionItemContainer (with single property item) to json file and back.

TEST_F(JsonItemContainerConverterTest, propertyContainerToFileAndBack)
{
    // creating container
    TagInfo tag = TagInfo::propertyTag("thickness", Constants::PropertyType);
    SessionItemContainer container(tag);

    // inserting single property item
    auto item = new PropertyItem;
    item->setData(42);
    EXPECT_TRUE(container.insertItem(item, 0));

    // converting top JSON and checking that it is valid JSON object
    auto converter = createConverter();
    auto json = converter->to_json(container);

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "propertyContainerToFileAndBack.json");
    TestUtils::SaveJson(json, fileName);

    // loading from file
    auto document = TestUtils::LoadJson(fileName);

    // creating second container with same layout, and updating it from JSON
    SessionItemContainer container2(tag);
    auto item2 = new PropertyItem;
    item2->setData(43);
    EXPECT_TRUE(container2.insertItem(item2, 0));
    converter->from_json(document.object(), container2);

    // Checking that item in container2 has been reused, and get same properties as item.
    EXPECT_EQ(container2.itemAt(0), item2);
    EXPECT_EQ(item->displayName(), item2->displayName());
    EXPECT_EQ(item->identifier(), item2->identifier());
    EXPECT_EQ(42, item2->data<int>());
}

//! SessionItemContainer (with universal tag and several items) to json object and back.

TEST_F(JsonItemContainerConverterTest, universalContainerToJsonAndBack)
{
    // creating container
    TagInfo tag = TagInfo::universalTag("items");
    SessionItemContainer container(tag);

    // inserting single property item
    const int n_max_items = 3;
    for (int i = 0; i < n_max_items; ++i) {
        auto item = new PropertyItem;
        item->setData(i + 42);
        EXPECT_TRUE(container.insertItem(item, 0));
    }

    // converting top JSON
    auto converter = createConverter();
    auto json = converter->to_json(container);

    // creating second container with same layout, but without items
    SessionItemContainer container2(tag);
    converter->from_json(json, container2);

    // Checking that container2 got same content as container
    EXPECT_EQ(container2.itemCount(), n_max_items);
    for (int i = 0; i < n_max_items; ++i) {
        EXPECT_EQ(container.itemAt(i)->identifier(), container2.itemAt(i)->identifier());
        EXPECT_EQ(container.itemAt(i)->data<int>(), container2.itemAt(i)->data<int>());
    }
}
