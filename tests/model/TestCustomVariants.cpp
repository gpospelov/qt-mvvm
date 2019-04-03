#include "comboproperty.h"
#include "customvariants.h"
#include "google_test.h"
#include "itemutils.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "taginfo.h"
#include <memory>

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
    QVariant undefined;
    QVariant int_variant = QVariant::fromValue(1);
    QVariant double_variant = QVariant::fromValue(42.0);
    QVariant string_variant = QVariant::fromValue(std::string("string"));
    std::vector<double> vec{1, 2};
    QVariant vector_variant = QVariant::fromValue(vec);

    // undefined variant
    EXPECT_TRUE(Utils::IsTheSame(undefined, QVariant()));
    EXPECT_FALSE(Utils::IsTheSame(undefined, int_variant));
    EXPECT_FALSE(Utils::IsTheSame(undefined, double_variant));
    EXPECT_FALSE(Utils::IsTheSame(undefined, string_variant));
    EXPECT_FALSE(Utils::IsTheSame(undefined, vector_variant));

    // int variant
    EXPECT_TRUE(Utils::IsTheSame(int_variant, int_variant));
    EXPECT_FALSE(Utils::IsTheSame(int_variant, undefined));
    EXPECT_FALSE(Utils::IsTheSame(int_variant, QVariant::fromValue(2)));
    EXPECT_FALSE(Utils::IsTheSame(int_variant, double_variant));
    EXPECT_FALSE(Utils::IsTheSame(int_variant, string_variant));
    EXPECT_FALSE(Utils::IsTheSame(int_variant, vector_variant));

    // double variant
    EXPECT_TRUE(Utils::IsTheSame(double_variant, double_variant));
    EXPECT_FALSE(Utils::IsTheSame(double_variant, undefined));
    EXPECT_FALSE(Utils::IsTheSame(double_variant, QVariant::fromValue(43.0)));
    EXPECT_FALSE(Utils::IsTheSame(double_variant, int_variant));
    EXPECT_FALSE(Utils::IsTheSame(double_variant, string_variant));
    EXPECT_FALSE(Utils::IsTheSame(double_variant, vector_variant));

    // string variant
    EXPECT_TRUE(Utils::IsTheSame(string_variant, string_variant));
    EXPECT_FALSE(Utils::IsTheSame(string_variant, undefined));
    EXPECT_FALSE(Utils::IsTheSame(string_variant, QVariant::fromValue(std::string("cde"))));
    EXPECT_FALSE(Utils::IsTheSame(string_variant, int_variant));
    EXPECT_FALSE(Utils::IsTheSame(string_variant, double_variant));
    EXPECT_FALSE(Utils::IsTheSame(string_variant, vector_variant));

    // vector variant
    std::vector<double> vec2{1, 2, 3}, vec3{1, 1};
    EXPECT_TRUE(Utils::IsTheSame(vector_variant, vector_variant));
    EXPECT_FALSE(Utils::IsTheSame(vector_variant, QVariant::fromValue(vec2)));
    EXPECT_FALSE(Utils::IsTheSame(vector_variant, QVariant::fromValue(vec3)));
    EXPECT_FALSE(Utils::IsTheSame(vector_variant, undefined));
    EXPECT_FALSE(Utils::IsTheSame(vector_variant, QVariant::fromValue(43.0)));
    EXPECT_FALSE(Utils::IsTheSame(vector_variant, int_variant));
    EXPECT_FALSE(Utils::IsTheSame(vector_variant, double_variant));
    EXPECT_FALSE(Utils::IsTheSame(vector_variant, string_variant));
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
