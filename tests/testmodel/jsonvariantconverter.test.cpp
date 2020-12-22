// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/serialization/jsonvariantconverter.h"

#include "folderbasedtest.h"
#include "google_test.h"
#include "test_utils.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/customvariants.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/variant_constants.h"
#include "mvvm/utils/reallimits.h"
#include <QColor>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <vector>

using namespace ModelView;

//! Test convertion of QVariant from/to QJsonObject.

class JsonVariantConverterTest : public FolderBasedTest {
public:
    JsonVariantConverterTest() : FolderBasedTest("test_JsonVariant") {}

    static QVariant ToJsonAndBack(const QVariant& variant)
    {
        JsonVariantConverter converter;
        auto json = converter.get_json(variant);
        return converter.get_variant(json);
    }
};

//! Invalid QVariant conversion.

TEST_F(JsonVariantConverterTest, invalidVariant)
{
    JsonVariantConverter converter;

    QVariant variant;

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_FALSE(reco_variant.isValid());
    EXPECT_EQ(variant, reco_variant);
}

//! Bool QVariant conversion.

TEST_F(JsonVariantConverterTest, boolVariant)
{
    JsonVariantConverter converter;

    const bool value(true);
    QVariant variant(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsBoolVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<bool>(), value);
    EXPECT_EQ(reco_variant.typeName(), Constants::bool_type_name);
    EXPECT_EQ(variant, reco_variant);

    EXPECT_EQ(ToJsonAndBack(true).value<bool>(), true);
    EXPECT_EQ(ToJsonAndBack(false).value<bool>(), false);
}

//! Int QVariant conversion.

TEST_F(JsonVariantConverterTest, intVariant)
{
    JsonVariantConverter converter;

    const int value(42);
    QVariant variant(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsIntVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<int>(), value);
    EXPECT_EQ(reco_variant.typeName(), Constants::int_type_name);
    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(std::string) conversion.

TEST_F(JsonVariantConverterTest, stringVariant)
{
    JsonVariantConverter converter;

    const std::string value("abc");
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsStdStringVariant(reco_variant));
    EXPECT_EQ(reco_variant.typeName(), Constants::string_type_name);
    EXPECT_EQ(reco_variant.value<std::string>(), value);

    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(double) conversion.

TEST_F(JsonVariantConverterTest, doubleVariant)
{
    JsonVariantConverter converter;

    double value(43.2);
    QVariant variant = QVariant::fromValue(value);
    EXPECT_EQ(variant.typeName(), Constants::double_type_name);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsDoubleVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<double>(), value);
    EXPECT_EQ(variant, reco_variant);

    // more numbers
    value = 1e-03;
    EXPECT_DOUBLE_EQ(ToJsonAndBack(value).value<double>(), value);
    value = 0.99e-7;
    EXPECT_DOUBLE_EQ(ToJsonAndBack(value).value<double>(), value);
    value = 3.14159265359;
    EXPECT_DOUBLE_EQ(ToJsonAndBack(value).value<double>(), value);
}

//! QVariant(double) conversion. Special value 43.0 which Qt likes to cast to int based variant.

TEST_F(JsonVariantConverterTest, doubleVariantWhichLooksAsInt)
{
    JsonVariantConverter converter;

    double value(43.0); // special value which Qt like to cast to int-based variant
    QVariant variant = QVariant::fromValue(value);
    EXPECT_EQ(variant.typeName(), Constants::double_type_name);
    EXPECT_TRUE(Utils::IsDoubleVariant(variant));

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsDoubleVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<double>(), value);
    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(std::vector<double>) conversion.

TEST_F(JsonVariantConverterTest, vectorOfDoubleVariant)
{
    JsonVariantConverter converter;

    const std::vector<double> value = {42.0, 43.0, 44.0};
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsDoubleVectorVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<std::vector<double>>(), value);
    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(ComboProperty) conversion.

TEST_F(JsonVariantConverterTest, comboPropertyVariant)
{
    JsonVariantConverter converter;

    ComboProperty value = ComboProperty::createFrom(std::vector<std::string>({"a1", "a2", "a3"}));
    value.setSelected("a1", false);
    value.setSelected("a2", true);
    value.setSelected("a3", true);

    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsComboVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<ComboProperty>(), value);
    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(QColor) conversion.

TEST_F(JsonVariantConverterTest, colorVariant)
{
    JsonVariantConverter converter;

    const QColor value(Qt::red);
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsColorVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<QColor>(), value);
    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(ExternalProperty) conversion.

TEST_F(JsonVariantConverterTest, extPropVariant)
{
    JsonVariantConverter converter;

    const ExternalProperty value("abc", QColor(Qt::green), "123");
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsExtPropertyVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<ExternalProperty>(), value);
    EXPECT_EQ(variant, reco_variant);
}

//! QVariant(RealLimits) convertion.

TEST_F(JsonVariantConverterTest, realLimitsVariant)
{
    JsonVariantConverter converter;

    RealLimits value = RealLimits::limited(1.0, 2.0);
    QVariant variant = QVariant::fromValue(value);

    // from variant to json object
    auto object = converter.get_json(variant);
    EXPECT_TRUE(converter.isVariant(object));

    // from json object to variant
    QVariant reco_variant = converter.get_variant(object);
    EXPECT_TRUE(Utils::IsRealLimitsVariant(reco_variant));
    EXPECT_EQ(reco_variant.value<RealLimits>(), value);
    EXPECT_EQ(variant, reco_variant);

    // more values
    value = RealLimits::positive();
    EXPECT_EQ(ToJsonAndBack(QVariant::fromValue(value)).value<RealLimits>(), value);
    value = RealLimits::nonnegative();
    EXPECT_EQ(ToJsonAndBack(QVariant::fromValue(value)).value<RealLimits>(), value);
    value = RealLimits::limited(0.123, 0.124);
    EXPECT_EQ(ToJsonAndBack(QVariant::fromValue(value)).value<RealLimits>(), value);
}

//! Writing variants to file and reading them back.

TEST_F(JsonVariantConverterTest, toFileAndBack)
{
    const std::string string_value("abc");
    const std::vector<double> vector_value = {42.1, 42.2, 42.3};
    ComboProperty combo = ComboProperty::createFrom({"a 1", "a 2", "a/3"});
    combo.setSelected("a 1", false);
    combo.setSelected("a 2", true);
    combo.setSelected("a/3", true);
    QColor color(Qt::red);
    ExternalProperty extprop("abc", QColor(Qt::green), "1-2-3");

    std::vector<QVariant> variants = {QVariant(),
                                      QVariant(true),
                                      QVariant(42),
                                      QVariant(42.3),
                                      QVariant(43.0),
                                      QVariant(43.1),
                                      QVariant(0.99e-7),
                                      QVariant(3.14159265359),
                                      QVariant::fromValue(string_value),
                                      QVariant::fromValue(vector_value),
                                      QVariant::fromValue(combo),
                                      QVariant::fromValue(color),
                                      QVariant::fromValue(extprop),
                                      QVariant::fromValue(RealLimits::positive()),
                                      QVariant::fromValue(RealLimits::limited(1.12, 2.32))};

    // preparing array of json objects
    JsonVariantConverter converter;
    QJsonArray json_array;
    for (auto var : variants)
        json_array.append(converter.get_json(var));

    // writing to file
    auto fileName = TestUtils::TestFileName(testDir(), "variants.json");
    TestUtils::SaveJson(json_array, fileName);

    // reading variants from file
    auto document = TestUtils::LoadJson(fileName);
    std::vector<QVariant> reco_variants;
    for (const auto x : document.array())
        reco_variants.push_back(converter.get_variant(x.toObject()));

    // comparing initial and reconstructed variants
    EXPECT_EQ(variants, reco_variants);
}
