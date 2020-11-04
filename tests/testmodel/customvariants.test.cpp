// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <QColor>
#include <functional>
#include <memory>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/taginfo.h>
#include <mvvm/model/variant_constants.h>

using namespace ModelView;

class CustomVariantsTest : public ::testing::Test
{
public:
    ~CustomVariantsTest();

    template <typename T> QVariant variantFromArgument(const T& value)
    {
        return QVariant::fromValue(value);
    }
};

CustomVariantsTest::~CustomVariantsTest() = default;

//! To keep under control implicit type conversion.

TEST_F(CustomVariantsTest, VariantFromTemplateArgument)
{
    EXPECT_EQ(variantFromArgument(true).typeName(), Constants::bool_type_name);
    EXPECT_EQ(variantFromArgument(1).typeName(), Constants::int_type_name);
    EXPECT_EQ(variantFromArgument(42.0).typeName(), Constants::double_type_name);
    EXPECT_EQ(variantFromArgument(std::string("abc")).typeName(), Constants::string_type_name);
}

//! Variant compatibility.

TEST_F(CustomVariantsTest, VariantName)
{
    const std::vector<double> vec{1, 2};
    const ComboProperty combo = ComboProperty::createFrom({"a1", "a2", "s3"});
    EXPECT_EQ(Utils::VariantName(QVariant()), Constants::invalid_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(true)), Constants::bool_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(1)), Constants::int_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(42.0)), Constants::double_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(std::string("string"))),
              Constants::string_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(vec)), Constants::vector_double_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(combo)), Constants::comboproperty_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(QColor(Qt::red))),
              Constants::qcolor_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(ExternalProperty())),
              Constants::extproperty_type_name);
    EXPECT_EQ(Utils::VariantName(QVariant::fromValue(RealLimits())),
              Constants::reallimits_type_name);
}

//! Variant compatibility.

TEST_F(CustomVariantsTest, CompatibleVariantTypes)
{
    QVariant undefined;
    QVariant bool_variant = QVariant::fromValue(true);
    QVariant int_variant = QVariant::fromValue(1);
    QVariant double_variant = QVariant::fromValue(42.0);
    QVariant string_variant = QVariant::fromValue(std::string("string"));
    std::vector<double> vec{1, 2};
    QVariant vector_variant = QVariant::fromValue(vec);
    ComboProperty combo = ComboProperty::createFrom({"a1", "a2", "s3"});
    QVariant combo_variant = QVariant::fromValue(combo);
    QVariant color_variant = QVariant::fromValue(QColor(Qt::red));
    QVariant extprop_variant = QVariant::fromValue(ExternalProperty());
    QVariant limits_variant = QVariant::fromValue(RealLimits());

    std::vector<QVariant> variants = {bool_variant,   int_variant,     double_variant,
                                      string_variant, vector_variant,  combo_variant,
                                      color_variant,  extprop_variant, limits_variant};
    for (size_t i = 0; i < variants.size(); ++i) {
        EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, variants[i]));
        EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(variants[i]));
        for (size_t j = 0; j < variants.size(); ++j) {
            if (i == j) {
                EXPECT_TRUE(Utils::VariantType(variants[i]) == Utils::VariantType(variants[j]));
                EXPECT_TRUE(Utils::CompatibleVariantTypes(variants[i], variants[j]));
            } else {
                EXPECT_FALSE(Utils::CompatibleVariantTypes(variants[i], variants[j]));
                EXPECT_FALSE(Utils::VariantType(variants[i]) == Utils::VariantType(variants[j]));
            }
        }
    }
}

//! Test variant equality reported by SessionItemUtils::isTheSame

TEST_F(CustomVariantsTest, IsTheSameVariant)
{
    const std::vector<double> vec1{1, 2};
    const std::vector<double> vec2{1, 2, 3};
    const ComboProperty combo1 = ComboProperty::createFrom({"a1", "a2"});
    const ComboProperty combo2 = ComboProperty::createFrom({"b1"});
    const ExternalProperty extprop1;
    const ExternalProperty extprop2("abc", QColor(Qt::red), "123");
    const RealLimits lim1;
    const RealLimits lim2 = RealLimits::limited(1.0, 2.0);

    ComboProperty combo3 = ComboProperty::createFrom({"e1", "e2"});
    ComboProperty combo4 = ComboProperty::createFrom({"e1", "e2"});
    combo3.setValue("e1");
    combo4.setValue("e2");

    std::vector<QVariant> variants = {QVariant(),
                                      QVariant::fromValue(true),
                                      QVariant::fromValue(false),
                                      QVariant::fromValue(1),
                                      QVariant::fromValue(2),
                                      QVariant::fromValue(42.0),
                                      QVariant::fromValue(43.0),
                                      QVariant::fromValue(std::string("string1")),
                                      QVariant::fromValue(std::string("string2")),
                                      QVariant::fromValue(vec1),
                                      QVariant::fromValue(vec2),
                                      QVariant::fromValue(combo1),
                                      QVariant::fromValue(combo2),
                                      QVariant::fromValue(QColor(Qt::red)),
                                      QVariant::fromValue(QColor(Qt::green)),
                                      QVariant::fromValue(extprop1),
                                      QVariant::fromValue(extprop2),
                                      QVariant::fromValue(lim1),
                                      QVariant::fromValue(lim2),
                                      QVariant::fromValue(combo3),
                                      QVariant::fromValue(combo4)};

    for (size_t i = 0; i < variants.size(); ++i) {
        for (size_t j = 0; j < variants.size(); ++j) {
            if (i == j)
                EXPECT_TRUE(Utils::IsTheSame(variants[i], variants[j]));
            else
                EXPECT_FALSE(Utils::IsTheSame(variants[i], variants[j]));
        }
    }
}

//! Checks if ComboProperty based variant is the same.

TEST_F(CustomVariantsTest, IsTheSameComboProperty)
{
    ComboProperty combo1 = ComboProperty::createFrom({"a1", "a2"});
    ComboProperty combo2 = ComboProperty::createFrom({"a1", "a2"});

    EXPECT_TRUE(Utils::IsTheSame(QVariant::fromValue(combo1), QVariant::fromValue(combo1)));

    combo1.setValue("a1");
    combo2.setValue("a2");
    EXPECT_FALSE(Utils::IsTheSame(QVariant::fromValue(combo1), QVariant::fromValue(combo2)));

    QVariant v1 = QVariant::fromValue(combo1);
    QVariant v2 = QVariant::fromValue(combo2);
    EXPECT_FALSE(Utils::IsTheSame(v1, v2));
}

//! Test toQtVAriant function.

TEST_F(CustomVariantsTest, toQtVariant)
{
    // from Variant based on std::string to variant based on QString
    QVariant stdstring_variant = QVariant::fromValue(std::string("abc"));
    QVariant qstring_variant = QVariant::fromValue(QString("abc"));
    QVariant converted = Utils::toQtVariant(stdstring_variant);

    EXPECT_FALSE(qstring_variant == stdstring_variant);
    EXPECT_TRUE(qstring_variant == converted);

    // Double variant should be unchanged
    QVariant value(42.0);
    EXPECT_TRUE(Utils::toQtVariant(value) == QVariant::fromValue(42.0));

    QVariant invalid;
    EXPECT_FALSE(Utils::toQtVariant(invalid).isValid());
}

//! Test translation of variants

TEST_F(CustomVariantsTest, toCustomVariant)
{
    // from Variant based on QString to variant based on std::string
    QVariant stdstring_variant = QVariant::fromValue(std::string("abc"));
    QVariant qstring_variant = QVariant::fromValue(QString("abc"));
    QVariant converted = Utils::toCustomVariant(qstring_variant);

    EXPECT_FALSE(qstring_variant == stdstring_variant);
    EXPECT_TRUE(stdstring_variant == converted);

    // Double variant should be unchanged
    QVariant value(42.0);
    EXPECT_TRUE(Utils::toCustomVariant(value) == QVariant::fromValue(42.0));

    QVariant invalid;
    EXPECT_FALSE(Utils::toCustomVariant(invalid).isValid());
}

//! Checks all functions related to variant types.

// FIXME replace tests in loop with parameterized tests

TEST_F(CustomVariantsTest, isVariantType)
{
    using is_variant_t = std::function<bool(const QVariant&)>;

    std::vector<std::pair<QVariant, is_variant_t>> data = {
        {QVariant::fromValue(true), Utils::IsBoolVariant},
        {QVariant::fromValue(1), Utils::IsIntVariant},
        {QVariant::fromValue(42.0), Utils::IsDoubleVariant},
        {QVariant::fromValue(ComboProperty()), Utils::IsComboVariant},
        {QVariant::fromValue(std::string("string1")), Utils::IsStdStringVariant},
        {QVariant::fromValue(std::vector<double>({1, 2})), Utils::IsDoubleVectorVariant},
        {QVariant::fromValue(QColor(Qt::red)), Utils::IsColorVariant},
        {QVariant::fromValue(ExternalProperty()), Utils::IsExtPropertyVariant},
        {QVariant::fromValue(RealLimits()), Utils::IsRealLimitsVariant}};

    for (size_t i = 0; i < data.size(); ++i) {
        auto is_variant_func = data[i].second;
        for (size_t j = 0; j < data.size(); ++j) {
            auto variant = data[j].first;
            if (i == j)
                EXPECT_TRUE(is_variant_func(variant));
            else
                EXPECT_FALSE(is_variant_func(variant));
        }
    }
}
