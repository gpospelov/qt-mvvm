#include "google_test.h"
#include "jsonvariant.h"
#include "test_utils.h"
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
