// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/editors/scientificspinbox.h"

#include "google_test.h"
#include <limits>

using namespace ModelView;

class ScientificSpinBoxTest : public ::testing::Test {
};

TEST_F(ScientificSpinBoxTest, testValueFromText)
{
    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    QDoubleValidator validator;
    validator.setLocale(locale);
    validator.setNotation(QDoubleValidator::ScientificNotation);

    auto to_value = [&validator](QString text) {
        return ScientificSpinBox::toDouble(text, validator, std::numeric_limits<double>::lowest(),
                                           std::numeric_limits<double>::max(), 0.1);
    };

    // translation fails
    EXPECT_EQ(0.1, to_value(QString("abcd")));
    EXPECT_EQ(0.1, to_value(QString("1,2")));
    EXPECT_EQ(0.1, to_value(QString("100,000,000.2")));
    EXPECT_EQ(0.1, to_value(QString("100.000.000.2")));
    EXPECT_EQ(0.1, to_value(QString("1e+2345")));
    EXPECT_EQ(0.1, to_value(QString("-1e+2345")));
    EXPECT_EQ(0.1, to_value(QString("1e-2345")));
    EXPECT_EQ(0.1, to_value(QString("-1e-2345")));
    EXPECT_EQ(0.1, to_value(QString("--0.1")));
    EXPECT_EQ(0.1, to_value(QString("-.e-12")));
    EXPECT_EQ(0.1, to_value(QString()));

    auto to_value_2 = [&validator](QString text) {
        return ScientificSpinBox::toDouble(text, validator, -0.1, 1e+7, 0.1);
    };

    // translation fails due to out-of-bounds condition
    EXPECT_EQ(0.1, to_value_2(QString("-0.2")));
    EXPECT_EQ(0.1, to_value_2(QString("-0.1e+1")));
    EXPECT_EQ(0.1, to_value_2(QString("1e+8")));

    // legitimate values
    EXPECT_EQ(-0.0999, to_value_2(QString("-0.0999")));
    EXPECT_EQ(-1e-13, to_value_2(QString("-.1e-12")));
    EXPECT_EQ(0.0, to_value_2(QString("0")));
    EXPECT_EQ(0.123, to_value_2(QString("0.123")));
    EXPECT_EQ(1e+6, to_value_2(QString("1e+6")));
    EXPECT_EQ(1.1e+6, to_value_2(QString("1.1e+6")));
    EXPECT_EQ(0.012, to_value_2(QString("0.012")));
}

TEST_F(ScientificSpinBoxTest, toString)
{
    int decimals = 3;
    auto to_string = [&decimals](double val) { return ScientificSpinBox::toString(val, decimals); };

    EXPECT_EQ(std::string("-123.45"), to_string(-123.45).toStdString());
    EXPECT_EQ(std::string("-100"), to_string(-99.9999).toStdString());
    EXPECT_EQ(std::string("-99.999"), to_string(-99.9994).toStdString());
    EXPECT_EQ(std::string("-10.123"), to_string(-10.12345).toStdString());
    EXPECT_EQ(std::string("-1"), to_string(-1.).toStdString());
    EXPECT_EQ(std::string("-0.1"), to_string(-0.1).toStdString());
    EXPECT_EQ(std::string("-0.1"), to_string(-0.1).toStdString());
    EXPECT_EQ(std::string("-9.99e-2"), to_string(-9.99e-2).toStdString());
    EXPECT_EQ(std::string("-1.266e-12"), to_string(-1.26555e-12).toStdString());
    EXPECT_EQ(std::string("0"), to_string(-0.0).toStdString());
    EXPECT_EQ(std::string("0"), to_string(0.0).toStdString());
    EXPECT_EQ(std::string("1e-12"), to_string(1.e-12).toStdString());
    EXPECT_EQ(std::string("1.23e-12"), to_string(1.23e-12).toStdString());
    EXPECT_EQ(std::string("1e-2"), to_string(1.e-2).toStdString());
    EXPECT_EQ(std::string("1.5e-2"), to_string(1.5e-2).toStdString());
    EXPECT_EQ(std::string("1.523e-2"), to_string(1.5234e-2).toStdString());
    EXPECT_EQ(std::string("9.99e-2"), to_string(9.99e-2).toStdString());
    EXPECT_EQ(std::string("1e-1"), to_string(9.9999e-2).toStdString());
    EXPECT_EQ(std::string("0.1"), to_string(0.1).toStdString());
    EXPECT_EQ(std::string("1"), to_string(1.).toStdString());
    EXPECT_EQ(std::string("1.1"), to_string(1.1).toStdString());
    EXPECT_EQ(std::string("1.123"), to_string(1.12345).toStdString());
    EXPECT_EQ(std::string("10.123"), to_string(10.12345).toStdString());
    EXPECT_EQ(std::string("99.9"), to_string(99.9).toStdString());
    EXPECT_EQ(std::string("99.999"), to_string(99.9994).toStdString());
    EXPECT_EQ(std::string("100"), to_string(99.9999).toStdString());
    EXPECT_EQ(std::string("123.45"), to_string(123.45).toStdString());
    EXPECT_EQ(std::string("1e+4"), to_string(1.e+4).toStdString());
    EXPECT_EQ(std::string("1.265e+12"), to_string(1.265e+12).toStdString());
    EXPECT_EQ(std::string("1.266e+12"), to_string(1.26555e+12).toStdString());

    decimals = 5;
    EXPECT_EQ(std::string("1.23e-12"), to_string(1.23e-12).toStdString());
    EXPECT_EQ(std::string("1.52346e-2"), to_string(1.523456e-2).toStdString());
    EXPECT_EQ(std::string("1e-1"), to_string(9.999999e-2).toStdString());
    EXPECT_EQ(std::string("1.12346"), to_string(1.123455).toStdString());
    EXPECT_EQ(std::string("10.12346"), to_string(10.123456).toStdString());
    EXPECT_EQ(std::string("99.9"), to_string(99.9).toStdString());
    EXPECT_EQ(std::string("100"), to_string(99.999999).toStdString());
    EXPECT_EQ(std::string("123.45"), to_string(123.45).toStdString());
    EXPECT_EQ(std::string("1.26556e+12"), to_string(1.265556e+12).toStdString());
}

TEST_F(ScientificSpinBoxTest, round)
{
    auto round_3 = [](double val) { return ScientificSpinBox::round(val, 3); };
    EXPECT_DOUBLE_EQ(1.232e-12, round_3(1.2323e-12));
    EXPECT_DOUBLE_EQ(0.123, round_3(0.1232));
    EXPECT_DOUBLE_EQ(1.002e+2, round_3(100.2));
}
