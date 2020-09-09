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

////! PropertyItem to json object and back.

//TEST_F(JsonItemConverterV2Test, propertyItemToJsonAndBack)
//{
//    auto converter = createConverter();

//    PropertyItem item;
//    item.setToolTip("abc");
//    auto object = converter->to_json(&item);

//    auto reco = converter->from_json(object);

//    EXPECT_EQ(reco->modelType(), item.modelType());
//    EXPECT_EQ(reco->displayName(), item.displayName());
//    EXPECT_EQ(reco->identifier(), item.identifier());

//    EXPECT_EQ(reco->toolTip(), std::string()); // tooltip is not preserved
//}
