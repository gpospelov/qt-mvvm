// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonitemconverter.h"

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/itemcatalogue.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionitemtags.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/serialization/jsonitem_types.h"
#include "mvvm/serialization/jsonitemformatassistant.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace ModelView;

//! Checks JsonItem class and its ability to convert SessionItems to json and back.

class JsonItemConverterTest : public FolderBasedTest {
public:
    class TestItem : public CompoundItem {
    public:
        TestItem() : CompoundItem("TestItem")
        {
            setToolTip("compound");
            addProperty("Thickness", 42)->setToolTip("thickness");
        }
    };

    class TestModel : public SessionModel {
    public:
        TestModel() : SessionModel("TestModel")
        {
            auto catalogue = std::make_unique<ModelView::ItemCatalogue>();
            catalogue->registerItem<TestItem>();
            setItemCatalogue(std::move(catalogue));
        }
    };

    JsonItemConverterTest()
        : FolderBasedTest("test_JsonItemConverter"), m_model(std::make_unique<TestModel>())
    {
    }

    std::unique_ptr<JsonItemConverter> createConverter()
    {
        ConverterContext context{m_model->factory(), ConverterMode::clone};
        return std::make_unique<JsonItemConverter>(context);
    }

private:
    std::unique_ptr<SessionModel> m_model;
};

//! PropertyItem to json object.

TEST_F(JsonItemConverterTest, propertyItemToJson)
{
    auto converter = createConverter();

    PropertyItem item;
    auto object = converter->to_json(&item);

    // this object represents SessionItem
    JsonItemFormatAssistant assistant;
    EXPECT_TRUE(assistant.isSessionItem(object));
}

//! PropertyItem to json object and back.

TEST_F(JsonItemConverterTest, propertyItemToJsonAndBack)
{
    auto converter = createConverter();

    PropertyItem item;
    item.setToolTip("abc");
    auto object = converter->to_json(&item);

    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->identifier(), item.identifier());
    EXPECT_EQ(reco->toolTip(), std::string("abc"));
}

//! PropertyItem to json file and back.

TEST_F(JsonItemConverterTest, propertyItemToFileAndBack)
{
    auto converter = createConverter();

    PropertyItem item;
    auto object = converter->to_json(&item);

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "propertyItemToFileAndBack.json");
    TestUtils::SaveJson(object, fileName);

    auto document = TestUtils::LoadJson(fileName);
    auto reco = converter->from_json(document.object());

    EXPECT_EQ(reco->parent(), nullptr);
    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->identifier(), item.identifier());
}

//! Parent and child to json object.

TEST_F(JsonItemConverterTest, parentAndChildToJsonAndBack)
{
    auto converter = createConverter();
    const std::string model_type(Constants::BaseType);

    auto parent = std::make_unique<SessionItem>(model_type);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child = parent->insertItem(std::make_unique<SessionItem>(model_type), TagRow::append());
    child->setDisplayName("child_name");

    // converting to json
    auto object = converter->to_json(parent.get());
    JsonItemFormatAssistant assistant;
    EXPECT_TRUE(assistant.isSessionItem(object));

    // converting json back to item
    auto reco_parent = converter->from_json(object);

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->modelType(), model_type);
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->itemTags()->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->model(), nullptr);

    // checking child reconstruction
    auto reco_child = reco_parent->getItem("defaultTag");
    EXPECT_EQ(reco_child->parent(), reco_parent.get());
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->modelType(), model_type);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->itemTags()->defaultTag(), "");
}

//! Parent and child to json file and back.

TEST_F(JsonItemConverterTest, parentAndChildToFileAndBack)
{
    auto converter = createConverter();
    const std::string model_type(Constants::BaseType);

    auto parent = std::make_unique<SessionItem>(model_type);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child = parent->insertItem(std::make_unique<SessionItem>(model_type), TagRow::append());
    child->setDisplayName("child_name");

    // converting to json
    auto object = converter->to_json(parent.get());
    JsonItemFormatAssistant assistant;
    EXPECT_TRUE(assistant.isSessionItem(object));

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "parentAndChildToFileAndBack.json");
    TestUtils::SaveJson(object, fileName);

    // converting document back to item
    auto document = TestUtils::LoadJson(fileName);
    auto reco_parent = converter->from_json(document.object());

    // checking parent reconstruction
    EXPECT_EQ(reco_parent->childrenCount(), 1);
    EXPECT_EQ(reco_parent->modelType(), model_type);
    EXPECT_EQ(reco_parent->displayName(), "parent_name");
    EXPECT_EQ(reco_parent->identifier(), parent->identifier());
    EXPECT_EQ(reco_parent->itemTags()->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->model(), nullptr);

    // checking child reconstruction
    auto reco_child = reco_parent->getItem("defaultTag");
    EXPECT_EQ(reco_child->parent(), reco_parent.get());
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->modelType(), model_type);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->itemTags()->defaultTag(), "");
}

//! TestItem to json file and back.

TEST_F(JsonItemConverterTest, testItemToFileAndBack)
{
    auto converter = createConverter();

    TestItem item;
    auto object = converter->to_json(&item);

    // saving object to file
    auto fileName = TestUtils::TestFileName(testDir(), "testItemToFileAndBack.json");
    TestUtils::SaveJson(object, fileName);

    auto document = TestUtils::LoadJson(fileName);
    auto reco = converter->from_json(document.object());

    EXPECT_EQ(reco->parent(), nullptr);
    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->identifier(), item.identifier());

    EXPECT_EQ(reco->toolTip(), "compound");
    // tooltip was preserved after the serialization
    EXPECT_EQ(reco->getItem("Thickness")->toolTip(), "thickness");
}
