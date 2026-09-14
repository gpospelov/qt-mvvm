// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/model/customvariants.h"

#include "google_test.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/model/externalproperty.h"
#include <QColor>
#include <QHash>
#include <cstddef>
#include <functional>
#include <string>
#include <utility>
#include <vector>

using namespace ModelView;

class CustomVariantsTest : public ::testing::Test {
public:
    template <typename T> QVariant variantFromArgument(const T& value)
    {
        return QVariant::fromValue(value);
    }
};

//! To keep under control implicit type conversion.

TEST_F(CustomVariantsTest, VariantFromTemplateArgument)
{
    EXPECT_EQ(variantFromArgument(true).userType(), QMetaType::fromType<bool>().id());
    EXPECT_EQ(variantFromArgument(1).userType(), QMetaType::fromType<int>().id());
    EXPECT_EQ(variantFromArgument(42.0).userType(), QMetaType::fromType<double>().id());
    EXPECT_EQ(variantFromArgument(std::string("abc")).userType(), QMetaType::fromType<std::string>().id());
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
        {QVariant::fromValue(RealLimits()), Utils::IsRealLimitsVariant}
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
