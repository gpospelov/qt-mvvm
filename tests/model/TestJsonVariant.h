#include <gtest/gtest.h>
#include "jsonvariant.h"
#include "jsonkeys.h"
#include "test_utils.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <vector>

//! Test convertion of QVariant from/to QJsonObject.

class TestJsonVariant : public ::testing::Test
{
public:
    ~TestJsonVariant();

    static const QString test_dir;
    static QJsonArray m_array;

    static void SetUpTestCase()
    {
        TestUtils::CreateTestDirectory(test_dir);
    }

    static void TearDownTestCase() {
        auto fileName = TestUtils::TestFileName(test_dir, "variants.json");
        TestUtils::SaveJson(m_array, fileName);
    }
};

const QString TestJsonVariant::test_dir = "test_JsonVariant";
QJsonArray TestJsonVariant::m_array = QJsonArray();

TestJsonVariant::~TestJsonVariant() = default;

//! Invalid QVariant convertion.

TEST_F(TestJsonVariant, invalidVariant)
{
    QVariant variant;

    // from variant to json object
    auto object = json::get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << json::variantTypeKey << json::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[json::variantTypeKey], json::invalid_type_name);
    EXPECT_TRUE(object[json::variantValueKey].isNull());

    // from json object to variant
    QJsonObject object2{
        {json::variantTypeKey, json::invalid_type_name},
        {json::variantValueKey, QJsonValue()}
    };
    QVariant variant2 = json::get_variant(object2);
    EXPECT_FALSE(variant2.isValid());

    // final comparison
    EXPECT_EQ(variant, variant2);
}

//! Int QVariant convertion.

TEST_F(TestJsonVariant, intVariant)
{
    const int value(42);
    QVariant variant(value);

    // from variant to json object
    auto object = json::get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << json::variantTypeKey << json::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[json::variantTypeKey], json::int_type_name);
    EXPECT_EQ(object[json::variantValueKey].toInt(), value);

    // from json object to variant
    QJsonObject object2{
        {json::variantTypeKey, json::int_type_name},
        {json::variantValueKey, value}
    };
    QVariant variant2 = json::get_variant(object2);
    EXPECT_EQ(variant2.toInt(), value);

    // final comparison
    EXPECT_EQ(variant, variant2);
}

//! QVariant(std::string) convertion.

TEST_F(TestJsonVariant, stringVariant)
{
    const std::string value("abc");
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = json::get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << json::variantTypeKey << json::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[json::variantTypeKey], json::string_type_name);
    QVariant var = object[json::variantValueKey].toVariant();
    // variant obtained from json is always based on QString, nave to convert std::string
    // to QString to make comparison
    EXPECT_EQ(object[json::variantValueKey].toString(), QString::fromStdString(value));

    // from json object to variant
    QJsonObject object2{
        {json::variantTypeKey, json::string_type_name},
        {json::variantValueKey, QString::fromStdString(value)}
    };
    QVariant variant2 = json::get_variant(object2);
    EXPECT_EQ(variant2.value<std::string>(), value);
}

//! QVariant(double) convertion.

TEST_F(TestJsonVariant, doubleVariant)
{
    const double value(42.3);
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = json::get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << json::variantTypeKey << json::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[json::variantTypeKey], json::double_type_name);
    EXPECT_EQ(object[json::variantValueKey].toDouble(), value);

    // from json object to variant
    QJsonObject object2{
        {json::variantTypeKey, json::double_type_name},
        {json::variantValueKey, value}
    };
    QVariant variant2 = json::get_variant(object2);
    EXPECT_EQ(variant2.toDouble(), value);

    // final comparison
    EXPECT_EQ(variant, variant2);
}

//! QVariant(std::vector<double>) convertion.

TEST_F(TestJsonVariant, vectorOfDoubleVariant)
{
    const std::vector<double> value = {42.0, 43.0, 44.0};
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = json::get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << json::variantTypeKey << json::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[json::variantTypeKey], json::vector_double_type_name);

    QJsonArray array = object[json::variantValueKey].toArray();
    std::vector<double> vec_expected;
    for ( auto x : object[json::variantValueKey].toArray()) {
        vec_expected.push_back(x.toDouble());
    }
    EXPECT_EQ(value, vec_expected);

    QVariant variant2 = json::get_variant(object);
    EXPECT_EQ(variant2.value<std::vector<double>>(), value);
}
