#include "google_test.h"
#include "sessionmodel.h"
#include "jsonitem.h"
#include "sessionitem.h"
#include "test_utils.h"
#include "taginfo.h"
#include <QJsonObject>
#include <QJsonArray>

using namespace ModelView;

//! Checks JsonItem class and its ability to convert SessionItems to json and back.

class TestJsonItem : public ::testing::Test
{
public:
    ~TestJsonItem();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }
};

TestJsonItem::~TestJsonItem() = default;
const QString TestJsonItem::test_dir = "test_JsonItem";


TEST_F(TestJsonItem, singleItem)
{
    const QString model_type("MultiLayer");

    JsonItem converter;
    std::unique_ptr<SessionItem> parent(new SessionItem(model_type.toStdString()));
    parent->registerTag(TagInfo::universalTag("defaultTag"), /*set_as_default*/true);

    auto child = new SessionItem("Layer");
    parent->insertItem(child, -1);

    auto object = converter.to_json(parent.get());

    // saving to file
    auto fileName = TestUtils::TestFileName(test_dir, "items.json");
    TestUtils::SaveJson(object, fileName);

}

