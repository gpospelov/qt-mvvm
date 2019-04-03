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

//! Comparing types of variant.

TEST_F(TestCustomVariants, VariantType)
{
    QVariant undefined;
    QVariant int_variant = QVariant::fromValue(1);
    QVariant double_variant = QVariant::fromValue(42.0);
    QVariant string_variant = QVariant::fromValue(std::string("abc"));
    std::vector<double> vec{1, 2};
    QVariant vector_variant = QVariant::fromValue(vec);

    EXPECT_TRUE(Utils::VariantType(undefined) == Utils::VariantType(QVariant()));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(int_variant));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(double_variant));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(string_variant));
    EXPECT_FALSE(Utils::VariantType(undefined) == Utils::VariantType(vector_variant));

    EXPECT_TRUE(Utils::VariantType(int_variant) == Utils::VariantType(QVariant::fromValue(2)));
    EXPECT_FALSE(Utils::VariantType(int_variant) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(int_variant) == Utils::VariantType(double_variant));
    EXPECT_FALSE(Utils::VariantType(int_variant) == Utils::VariantType(string_variant));
    EXPECT_FALSE(Utils::VariantType(int_variant) == Utils::VariantType(vector_variant));

    EXPECT_TRUE(Utils::VariantType(double_variant)
                == Utils::VariantType(QVariant::fromValue(43.0)));
    EXPECT_FALSE(Utils::VariantType(double_variant) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(double_variant) == Utils::VariantType(int_variant));
    EXPECT_FALSE(Utils::VariantType(double_variant) == Utils::VariantType(string_variant));
    EXPECT_FALSE(Utils::VariantType(double_variant) == Utils::VariantType(vector_variant));

    EXPECT_TRUE(Utils::VariantType(string_variant)
                == Utils::VariantType(QVariant::fromValue(std::string("cde"))));
    EXPECT_FALSE(Utils::VariantType(string_variant) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(string_variant) == Utils::VariantType(int_variant));
    EXPECT_FALSE(Utils::VariantType(string_variant) == Utils::VariantType(double_variant));
    EXPECT_FALSE(Utils::VariantType(string_variant) == Utils::VariantType(vector_variant));

    std::vector<double> vec2{1, 2};
    EXPECT_TRUE(Utils::VariantType(vector_variant)
                == Utils::VariantType(QVariant::fromValue(vec2)));
    EXPECT_FALSE(Utils::VariantType(vector_variant) == Utils::VariantType(undefined));
    EXPECT_FALSE(Utils::VariantType(vector_variant) == Utils::VariantType(int_variant));
    EXPECT_FALSE(Utils::VariantType(vector_variant) == Utils::VariantType(double_variant));
    EXPECT_FALSE(Utils::VariantType(vector_variant) == Utils::VariantType(string_variant));
}

//! Variant compatibility.
//! For the moment, undefined variant

TEST_F(TestCustomVariants, CompatibleVariantTypes)
{
    QVariant undefined;
    QVariant int_variant = QVariant::fromValue(1);
    QVariant double_variant = QVariant::fromValue(42.0);
    QVariant string_variant = QVariant::fromValue(std::string("string"));
    std::vector<double> vec{1, 2};
    QVariant vector_variant = QVariant::fromValue(vec);

    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, int_variant));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, double_variant));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, string_variant));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(undefined, vector_variant));

    EXPECT_TRUE(Utils::CompatibleVariantTypes(int_variant, int_variant));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(int_variant, undefined));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(int_variant, double_variant));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(int_variant, string_variant));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(int_variant, vector_variant));

    EXPECT_TRUE(Utils::CompatibleVariantTypes(double_variant, double_variant));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(double_variant, undefined));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(double_variant, string_variant));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(double_variant, int_variant));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(double_variant, vector_variant));

    EXPECT_TRUE(Utils::CompatibleVariantTypes(string_variant, string_variant));
    EXPECT_TRUE(Utils::CompatibleVariantTypes(string_variant, undefined));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(string_variant, int_variant));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(string_variant, double_variant));
    EXPECT_FALSE(Utils::CompatibleVariantTypes(string_variant, vector_variant));
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
