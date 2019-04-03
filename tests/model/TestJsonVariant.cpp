#include "google_test.h"
#include "jsonvariant.h"
#include "test_utils.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <vector>

using namespace ModelView;

//! Test convertion of QVariant from/to QJsonObject.

class TestJsonVariant : public ::testing::Test
{
public:
    ~TestJsonVariant();

    static const QString test_dir;

    static void SetUpTestCase() { TestUtils::CreateTestDirectory(test_dir); }
};

const QString TestJsonVariant::test_dir = "test_JsonVariant";

TestJsonVariant::~TestJsonVariant() = default;

//! Invalid QVariant convertion.

TEST_F(TestJsonVariant, invalidVariant)
{
    JsonVariant converter;

    QVariant variant;

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_FALSE(reco_variant.isValid());
    EXPECT_EQ(variant, reco_variant);
}

//! Int QVariant convertion.

TEST_F(TestJsonVariant, intVariant)
{
    JsonVariant converter;

    const int value(42);
    QVariant variant(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(reco_variant.isValid());
    EXPECT_EQ(reco_variant.toInt(), value);

    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(std::string) convertion.

TEST_F(TestJsonVariant, stringVariant)
{
    JsonVariant converter;

    const std::string value("abc");
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(reco_variant.isValid());
    EXPECT_EQ(reco_variant.value<std::string>(), value);

    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(double) convertion.

TEST_F(TestJsonVariant, doubleVariant)
{
    JsonVariant converter;

    const double value(42.3);
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(reco_variant.isValid());
    EXPECT_EQ(reco_variant.toDouble(), value);
    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(std::vector<double>) convertion.

TEST_F(TestJsonVariant, vectorOfDoubleVariant)
{
    JsonVariant converter;

    const std::vector<double> value = {42.0, 43.0, 44.0};
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(reco_variant.isValid());
    EXPECT_EQ(reco_variant.value<std::vector<double>>(), value);
    EXPECT_EQ(variant, reco_variant);
}

//! Writing variants to file and reading them back.

TEST_F(TestJsonVariant, toFileAndBack)
{
    const int int_value(42);
    const double double_value(42.3);
    const std::string string_value("abc");
    const std::vector<double> vector_value = {42.1, 42.2, 42.3};

    std::vector<QVariant> variants = {QVariant(), QVariant(int_value), QVariant(double_value),
                                      QVariant::fromValue(string_value),
                                      QVariant::fromValue(vector_value)};

    // preparing array of json objects
    JsonVariant converter;
    QJsonArray json_array;
    for (auto var : variants)
        json_array.append(converter.get_json(var));

    // writing to file
    auto fileName = TestUtils::TestFileName(test_dir, "variants.json");
    TestUtils::SaveJson(json_array, fileName);

    // reading variants from file
    auto document = TestUtils::LoadJson(fileName);
    std::vector<QVariant> reco_variants;
    for (const auto x : document.array())
        reco_variants.push_back(converter.get_variant(x.toObject()));

    // comparing initial and reconstructed variants
    EXPECT_EQ(variants, reco_variants);
}
