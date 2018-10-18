#include <gtest/gtest.h>
#include "jsonvariant.h"
#include "test_utils.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
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
    JsonVariant converter;

    QVariant variant;

    // from variant to json object
    auto object = converter.get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << JsonVariant::variantTypeKey << JsonVariant::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[JsonVariant::variantTypeKey], JsonVariant::invalid_type_name);
    EXPECT_TRUE(object[JsonVariant::variantValueKey].isNull());

    // from json object to variant
    QJsonObject object2{
        {JsonVariant::variantTypeKey, JsonVariant::invalid_type_name},
        {JsonVariant::variantValueKey, QJsonValue()}
    };
    QVariant variant2 = converter.get_variant(object2);
    EXPECT_FALSE(variant2.isValid());

    // final comparison
    EXPECT_EQ(variant, variant2);
}

//! Int QVariant convertion.

TEST_F(TestJsonVariant, intVariant)
{
    JsonVariant converter;

    const int value(42);
    QVariant variant(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << JsonVariant::variantTypeKey << JsonVariant::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[JsonVariant::variantTypeKey], JsonVariant::int_type_name);
    EXPECT_EQ(object[JsonVariant::variantValueKey].toInt(), value);

    // from json object to variant
    QJsonObject object2{
        {JsonVariant::variantTypeKey, JsonVariant::int_type_name},
        {JsonVariant::variantValueKey, value}
    };
    QVariant variant2 = converter.get_variant(object2);
    EXPECT_EQ(variant2.toInt(), value);

    // final comparison
    EXPECT_EQ(variant, variant2);
}

//! QVariant(std::string) convertion.

TEST_F(TestJsonVariant, stringVariant)
{
    JsonVariant converter;

    const std::string value("abc");
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << JsonVariant::variantTypeKey << JsonVariant::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[JsonVariant::variantTypeKey], JsonVariant::string_type_name);
    QVariant var = object[JsonVariant::variantValueKey].toVariant();
    // variant obtained from json is always based on QString, nave to convert std::string
    // to QString to make comparison
    EXPECT_EQ(object[JsonVariant::variantValueKey].toString(), QString::fromStdString(value));

    // from json object to variant
    QJsonObject object2{
        {JsonVariant::variantTypeKey, JsonVariant::string_type_name},
        {JsonVariant::variantValueKey, QString::fromStdString(value)}
    };
    QVariant variant2 = converter.get_variant(object2);
    EXPECT_EQ(variant2.value<std::string>(), value);
}

//! QVariant(double) convertion.

TEST_F(TestJsonVariant, doubleVariant)
{
    JsonVariant converter;

    const double value(42.3);
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << JsonVariant::variantTypeKey << JsonVariant::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[JsonVariant::variantTypeKey], JsonVariant::double_type_name);
    EXPECT_EQ(object[JsonVariant::variantValueKey].toDouble(), value);

    // from json object to variant
    QJsonObject object2{
        {JsonVariant::variantTypeKey, JsonVariant::double_type_name},
        {JsonVariant::variantValueKey, value}
    };
    QVariant variant2 = converter.get_variant(object2);
    EXPECT_EQ(variant2.toDouble(), value);

    // final comparison
    EXPECT_EQ(variant, variant2);
}

//! QVariant(std::vector<double>) convertion.

TEST_F(TestJsonVariant, vectorOfDoubleVariant)
{
    JsonVariant converter;

    const std::vector<double> value = {42.0, 43.0, 44.0};
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    m_array.append(object);

    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << JsonVariant::variantTypeKey << JsonVariant::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[JsonVariant::variantTypeKey], JsonVariant::vector_double_type_name);

    QJsonArray array = object[JsonVariant::variantValueKey].toArray();
    std::vector<double> vec_expected;
    for ( auto x : object[JsonVariant::variantValueKey].toArray()) {
        vec_expected.push_back(x.toDouble());
    }
    EXPECT_EQ(value, vec_expected);

    QVariant variant2 = converter.get_variant(object);
    EXPECT_EQ(variant2.value<std::vector<double>>(), value);
}
