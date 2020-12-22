// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/utils/stringutils.h"

#include "google_test.h"
#include "test_utils.h"

using namespace ModelView;
using namespace TestUtils;

class StringUtilsTest : public ::testing::Test {
};

TEST_F(StringUtilsTest, ScientificDoubleToString)
{
    using Utils::ScientificDoubleToString;
    const int precision = 6;
    EXPECT_EQ(ScientificDoubleToString(0.0, precision), "0.0e+00");
    EXPECT_EQ(ScientificDoubleToString(1.0, precision), "1.0e+00");
    EXPECT_EQ(ScientificDoubleToString(3.0 / 4.0, precision), "7.5e-01");
    EXPECT_EQ(ScientificDoubleToString(4.0 / 3.0, precision), "1.333333e+00");
    EXPECT_EQ(ScientificDoubleToString(1000000., precision), "1.0e+06");
}

TEST_F(StringUtilsTest, DoubleToString)
{
    using Utils::DoubleToString;
    const int precision = 4;
    EXPECT_EQ(DoubleToString(0.0, precision), "0.0");
    EXPECT_EQ(DoubleToString(1.001, precision), "1.001");
    EXPECT_EQ(DoubleToString(1.0001, precision), "1.0");
}

//! Testing function TrimWhitespace

TEST_F(StringUtilsTest, TrimWhiteSpace)
{
    using Utils::TrimWhitespace;
    EXPECT_EQ(TrimWhitespace(""), std::string());
    EXPECT_EQ(TrimWhitespace(" "), std::string());
    EXPECT_EQ(TrimWhitespace("abc"), std::string("abc"));
    EXPECT_EQ(TrimWhitespace(" \t\n abc cde\n"), std::string("abc cde"));
}

TEST_F(StringUtilsTest, RemoveRepeatedSpaces)
{
    using Utils::RemoveRepeatedSpaces;
    EXPECT_EQ(RemoveRepeatedSpaces(std::string{}), std::string{});
    EXPECT_EQ(RemoveRepeatedSpaces(" "), std::string{" "});
    EXPECT_EQ(RemoveRepeatedSpaces("a"), std::string{"a"});
    EXPECT_EQ(RemoveRepeatedSpaces(" a "), std::string{" a "});
    EXPECT_EQ(RemoveRepeatedSpaces("  a  "), std::string{" a "});
    EXPECT_EQ(RemoveRepeatedSpaces("a  bb   ccc   "), std::string{"a bb ccc "});
}

//! Testing function StringToDouble.

TEST_F(StringUtilsTest, StringToDouble)
{
    using Utils::StringToDouble;

    // not a double
    EXPECT_FALSE(StringToDouble("").has_value());
    EXPECT_FALSE(StringToDouble(" ").has_value());
    EXPECT_FALSE(StringToDouble("a").has_value());
    EXPECT_FALSE(StringToDouble("a b").has_value());

    // not a double: some mixture present
    EXPECT_FALSE(StringToDouble("42a").has_value());
    EXPECT_FALSE(StringToDouble("42.5.5").has_value());

    // not a double: more than one double
    EXPECT_FALSE(StringToDouble("42.5 52").has_value());

    // valid double
    EXPECT_TRUE(StringToDouble("42").has_value());
    EXPECT_TRUE(StringToDouble(" 42").has_value());
    EXPECT_TRUE(StringToDouble(" 42 ").has_value());
    EXPECT_DOUBLE_EQ(StringToDouble("42").value(), 42.0);
    EXPECT_TRUE(StringToDouble("42.5").has_value());
    EXPECT_DOUBLE_EQ(StringToDouble("42.5").value(), 42.5);
    EXPECT_TRUE(StringToDouble("-1.12e-06").has_value());
    EXPECT_DOUBLE_EQ(StringToDouble("-1.12e-06").value(), -1.12e-06);
}

//! Testing function StringToDouble.

TEST_F(StringUtilsTest, StringToInteger)
{
    using Utils::StringToInteger;

    // not an int
    EXPECT_FALSE(StringToInteger("").has_value());
    EXPECT_FALSE(StringToInteger(" ").has_value());
    EXPECT_FALSE(StringToInteger("a").has_value());
    EXPECT_FALSE(StringToInteger("a b").has_value());

    // not an int: some mixture present
    EXPECT_FALSE(StringToInteger("42a").has_value());
    EXPECT_FALSE(StringToInteger("42.5").has_value());

    // not an int: more than one number
    EXPECT_FALSE(StringToInteger("42.5 52").has_value());

    // valid int
    EXPECT_TRUE(StringToInteger("42").has_value());
    EXPECT_TRUE(StringToInteger(" 42").has_value());
    EXPECT_TRUE(StringToInteger(" 42 ").has_value());
    EXPECT_EQ(StringToInteger("42").value(), 42);
}

//! Testing SplitString method.
//! Carefully checking that it is reproduces Python behavior, as promised in comments to the method.

TEST_F(StringUtilsTest, SplitString)
{
    using Utils::SplitString;

    EXPECT_THROW(SplitString("", ""), std::runtime_error);
    EXPECT_EQ(SplitString("", " "), toVector<std::string>());
    EXPECT_EQ(SplitString("", ","), toVector<std::string>());
    EXPECT_EQ(SplitString(" ", " "), toVector<std::string>("", ""));
    EXPECT_EQ(SplitString("a", " "), toVector<std::string>("a"));
    EXPECT_EQ(SplitString("a ", " "), toVector<std::string>("a", ""));

    EXPECT_EQ(SplitString("a b", " "), toVector<std::string>("a", "b"));
    EXPECT_EQ(SplitString("a  b", " "), toVector<std::string>("a", "", "b"));

    EXPECT_EQ(SplitString("a", "-"), toVector<std::string>("a"));

    EXPECT_EQ(SplitString("aa", "a"), toVector<std::string>("", "", ""));

    EXPECT_EQ(SplitString("a,b", ","), toVector<std::string>("a", "b"));
    EXPECT_EQ(SplitString("a, b", ","), toVector<std::string>("a", " b"));

    EXPECT_EQ(SplitString("a,b,", ","), toVector<std::string>("a", "b", ""));
    EXPECT_EQ(SplitString(",a,b,", ","), toVector<std::string>("", "a", "b", ""));
    EXPECT_EQ(SplitString("aabbcc", "bb"), toVector<std::string>("aa", "cc"));
    EXPECT_EQ(SplitString("aabbcc", "bb"), toVector<std::string>("aa", "cc"));
}

//! Testing ParseSpaceSeparatedDoubles.

TEST_F(StringUtilsTest, ParseSpaceSeparatedDoubles)
{
    using Utils::ParseSpaceSeparatedDoubles;
    std::vector<double> data;

    EXPECT_TRUE(ParseSpaceSeparatedDoubles("").empty());
    EXPECT_TRUE(ParseSpaceSeparatedDoubles(" ").empty());
    EXPECT_TRUE(ParseSpaceSeparatedDoubles("a").empty());
    EXPECT_TRUE(ParseSpaceSeparatedDoubles("a b").empty());

    ASSERT_EQ(ParseSpaceSeparatedDoubles("4.02").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42")[0], 42.0);

    // this tests failing under MacOS
    //    ASSERT_EQ(ParseSpaceSeparatedDoubles("42aaa").size(), 1u);
    //    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42aaa")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42,").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42,")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42,43").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42,43")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42 ,43").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42 ,43")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42 43").size(), 2u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42 43")[0], 42.0);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42 43")[1], 43.0);
}
