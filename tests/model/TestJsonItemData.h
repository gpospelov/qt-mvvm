#include <gtest/gtest.h>
#include "jsonitemdata.h"
#include "test_utils.h"
#include <QDebug>

//! Test convertion of SessionItemData from/to QJsonObject.

class TestItemDataConverter : public ::testing::Test
{
public:
    ~TestItemDataConverter();

    static const QString test_dir;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }

};

const QString TestItemDataConverter::test_dir = "test_JsonItemData";

TestItemDataConverter::~TestItemDataConverter() = default;

//! Invalid QVariant convertion.

TEST_F(TestItemDataConverter, initialState)
{
    SessionItemData data;
    const int role = Qt::UserRole + 1;

    data.setData(QVariant::fromValue(42), role);
    data.setData(QVariant::fromValue(1.23), role+1);
    data.setData(QVariant::fromValue(std::string("abc")), role+2);

    QJsonArray array = JsonItemData::get_json(data);

    auto fileName = TestUtils::TestFileName(test_dir, "itemdata.json");
    TestUtils::SaveJson(array, fileName);

    EXPECT_EQ(1, 1);
}
