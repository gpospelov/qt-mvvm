#include "comboproperty.h"
#include "customvariants.h"
#include "google_test.h"
#include "itemutils.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include <memory>
#include <functional>

using namespace ModelView;

class TestCustomVariants : public ::testing::Test
{
public:
    ~TestCustomVariants();
};

TestCustomVariants::~TestCustomVariants() = default;

//! Variant compatibility.

TEST_F(TestCustomVariants, CompatibleVariantTypes)
{
    QVariant undefined;
    QVariant int_variant = QVariant::fromValue(1);
    QVariant double_variant = QVariant::fromValue(42.0);
    QVariant string_variant = QVariant::fromValue(std::string("string"));
    std::vector<double> vec{1, 2};
    QVariant vector_variant = QVariant::fromValue(vec);
    ComboProperty combo = ComboProperty::createFrom({"a1", "a2", "s3"});
    QVariant combo_variant = combo.variant();

    std::vector<QVariant> variants = {int_variant, double_variant, string_variant, vector_variant,
                                      combo_variant};
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

TEST_F(TestCustomVariants, IsTheSameVariant)
{
    const std::vector<double> vec1{1, 2};
    const std::vector<double> vec2{1, 2, 3};
    const ComboProperty combo1 = ComboProperty::createFrom({"a1", "a2"});
    const ComboProperty combo2 = ComboProperty::createFrom({"b1"});

    std::vector<QVariant> variants = {
        QVariant(),
        QVariant::fromValue(1), QVariant::fromValue(2),
        QVariant::fromValue(42.0), QVariant::fromValue(43.0),
        QVariant::fromValue(std::string("string1")), QVariant::fromValue(std::string("string2")),
        QVariant::fromValue(vec1), QVariant::fromValue(vec2),
        combo1.variant(), combo2.variant()
    };

    for (size_t i = 0; i < variants.size(); ++i) {
        for (size_t j = 0; j < variants.size(); ++j) {
            if (i == j)
                EXPECT_TRUE(Utils::IsTheSame(variants[i], variants[j]));
            else
                EXPECT_FALSE(Utils::IsTheSame(variants[i], variants[j]));
        }
    }
}

//! Test translation of variants

TEST_F(TestCustomVariants, variantTranslation)
{
    // from Variant based on std::string to variant based on QString
    QVariant stdstring_variant = QVariant::fromValue(std::string("abc"));
    QVariant qstring_variant = Utils::toQtVariant(stdstring_variant);
    QVariant expected("abc");
    EXPECT_FALSE(qstring_variant == stdstring_variant);
    EXPECT_TRUE(qstring_variant == expected);

    // from variant based on QString to variant based on std::string
    qstring_variant = QVariant::fromValue(QString("qwerty"));
    stdstring_variant = Utils::toCustomVariant(qstring_variant);
    expected = QVariant::fromValue(std::string("qwerty"));
    EXPECT_TRUE(stdstring_variant == expected);

    // Double variant should be unchanged
    QVariant value(42.0);
    EXPECT_TRUE(Utils::toCustomVariant(value) == QVariant::fromValue(42.0));
    EXPECT_TRUE(Utils::toQtVariant(value) == QVariant::fromValue(42.0));
}

//! Checks all functions related to variant types.

// FIXME replace tests in loop with parameterized tests

TEST_F(TestCustomVariants, isVariantType)
{
    using is_variant_t = std::function<bool(const QVariant&)>;

    std::vector<std::pair<QVariant, is_variant_t>> data = {
        {QVariant::fromValue(true), Utils::IsBoolVariant},
        {QVariant::fromValue(1), Utils::IsIntVariant},
        {QVariant::fromValue(42.0), Utils::IsDoubleVariant},
        {QVariant::fromValue(ComboProperty()), Utils::IsComboVariant},
        {QVariant::fromValue(std::string("string1")), Utils::IsStdStringVariant},
        {QVariant::fromValue(std::vector<double>({1, 2})), Utils::IsDoubleVectorVariant}
    };

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
