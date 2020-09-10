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
#include <QJsonDocument>
#include <QJsonObject>
#include <mvvm/model/compounditem.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/serialization/jsonitemconverter_v2.h>
#include <mvvm/serialization/jsonitemformatassistant.h>

using namespace ModelView;

//! Checks JsonItem class and its ability to convert SessionItems to json and back.

class JsonItemConverterV2Test : public FolderBasedTest
{
public:
    JsonItemConverterV2Test()
        : FolderBasedTest("test_JsonItemConverterV2"), m_model(std::make_unique<SessionModel>())
    {
    }
    ~JsonItemConverterV2Test();

    std::unique_ptr<JsonItemConverterV2> createConverter()
    {
        return std::make_unique<JsonItemConverterV2>(m_model->factory());
    }

private:
    std::unique_ptr<SessionModel> m_model;
};

JsonItemConverterV2Test::~JsonItemConverterV2Test() = default;

//! PropertyItem to json object.

TEST_F(JsonItemConverterV2Test, propertyItemToJson)
{
    auto converter = createConverter();

    PropertyItem item;
    auto object = converter->to_json(&item);

    // this object represents SessionItem
    JsonItemFormatAssistant assistant;
    EXPECT_TRUE(assistant.isSessionItem(object));
}

//! PropertyItem to json object and back.

TEST_F(JsonItemConverterV2Test, propertyItemToJsonAndBack)
{
    auto converter = createConverter();

    PropertyItem item;
    item.setToolTip("abc");
    auto object = converter->to_json(&item);

    auto reco = converter->from_json(object);

    EXPECT_EQ(reco->modelType(), item.modelType());
    EXPECT_EQ(reco->displayName(), item.displayName());
    EXPECT_EQ(reco->identifier(), item.identifier());

    EXPECT_EQ(reco->toolTip(), std::string()); // tooltip is not preserved
}

//! PropertyItem to json file and back.

TEST_F(JsonItemConverterV2Test, propertyItemToFileAndBack)
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

TEST_F(JsonItemConverterV2Test, parentAndChildToJsonAndBack)
{
    auto converter = createConverter();
    const std::string model_type(Constants::BaseType);

    auto parent = std::make_unique<SessionItem>(model_type);
    parent->setDisplayName("parent_name");
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/ true);
    auto child = new SessionItem(model_type);
    child->setDisplayName("child_name");
    parent->insertItem(child, TagRow::append());

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
    EXPECT_EQ(reco_parent->defaultTag(), "defaultTag");
    EXPECT_EQ(reco_parent->model(), nullptr);

    // checking child reconstruction
    auto reco_child = reco_parent->getItem("defaultTag");
    EXPECT_EQ(reco_child->parent(), reco_parent.get());
    EXPECT_EQ(reco_child->childrenCount(), 0);
    EXPECT_EQ(reco_child->modelType(), model_type);
    EXPECT_EQ(reco_child->displayName(), "child_name");
    EXPECT_EQ(reco_child->identifier(), child->identifier());
    EXPECT_EQ(reco_child->defaultTag(), "");
}


