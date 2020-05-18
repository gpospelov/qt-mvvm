// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "importlinefilter.h"
#include "test_utils.h"

#include <cmath>
#include <map>
#include <string>
#include <vector>

using namespace DataImportLogic;

//! Test the data column item
class LineFilterTest : public ::testing::Test
{
public:
    ~LineFilterTest();
    std::map<std::string, char> m_separators{
        {"Space ( )", ' '}, {"Comma (,)", ','}, {"Semicolon (;)", ';'}, {"Pipe (|)", '|'},
        {"Colon (:)", ':'}, {"Tab", '\t'},      {"Quote (\')", '\''},   {"Apostrophe (\")", '\"'}};
};

LineFilterTest::~LineFilterTest() = default;

//! Test default constructor
TEST_F(LineFilterTest, defaultContructor)
{
    LineFilter line_filter("default_name");
}

//! Test the normal setters and getters
TEST_F(LineFilterTest, setterGetterTest)
{
    LineFilter line_filter("default_name");
    line_filter.setSeparators(&m_separators);

    std::string name = "default_name";
    bool active = true;
    std::string type_string = "Header";
    std::string separator_name = "Space ( )";
    std::string color_string = "blue";
    int start_line = 1;
    int end_line = 2;

    line_filter.setName(name);
    line_filter.setActive(active);
    line_filter.setType(type_string);
    line_filter.setSeparator(separator_name);
    line_filter.setColor(color_string);
    line_filter.setStart(start_line);
    line_filter.setEnd(end_line);

    EXPECT_EQ(name, line_filter.name());
    EXPECT_EQ(active, line_filter.active());
    EXPECT_EQ(type_string, line_filter.type());
    EXPECT_EQ(separator_name, line_filter.separator());
    EXPECT_EQ(color_string, line_filter.color());
    EXPECT_EQ(start_line, line_filter.start());
    EXPECT_EQ(end_line, line_filter.end());
}

//! Test ignore string setter and getter
TEST_F(LineFilterTest, ignoreStringTest)
{
    LineFilter line_filter("default_name");

    std::string ignore_string = "#,@";
    std::vector<std::string> compare_ignore{"#", "@"};

    line_filter.setIgnoreString(ignore_string);

    EXPECT_EQ(ignore_string, line_filter.ignoreString());
    EXPECT_EQ(compare_ignore, line_filter.ignoreStrings());
}

//! Test the color generation with active filter in range
TEST_F(LineFilterTest, processColorsActiveRangeTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = 10;
    std::string color = "blue";

    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setColor(color);

    std::vector<std::string> test_color(20, "black");
    std::vector<std::string> compare_color(test_color.size(), color);
    for (int i = 0; i < start; ++i) {
        compare_color[i] = "black";
    }
    for (int i = end; i < compare_color.size(); ++i) {
        compare_color[i] = "black";
    }

    line_filter.processColors(test_color);
    EXPECT_EQ(test_color, compare_color);
}

//! Test the color generation with active filter from start to end of file (EOF)
TEST_F(LineFilterTest, processColorsActiveEOFTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = -1;
    std::string color = "blue";

    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setColor(color);

    std::vector<std::string> test_color(20, "black");
    std::vector<std::string> compare_color(test_color.size(), color);
    for (int i = 0; i < start; ++i) {
        compare_color[i] = "black";
    }

    line_filter.processColors(test_color);
    EXPECT_EQ(test_color, compare_color);
}

//! Test the color generation with inactive filter from start to end of file (EOF)
TEST_F(LineFilterTest, processColorsInactiveEOFTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = -1;
    std::string color = "blue";

    line_filter.setActive(false);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setColor(color);

    std::vector<std::string> test_color(20, "black");
    std::vector<std::string> compare_color(test_color.size(), "black");

    line_filter.processColors(test_color);
    EXPECT_EQ(test_color, compare_color);
}

//! Test the separator generation with active filter in range
TEST_F(LineFilterTest, processSeparatorActiveRangeTest)
{
    LineFilter line_filter("default_name");
    line_filter.setSeparators(&m_separators);

    int start = 2;
    int end = -1;
    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);

    std::vector<char> test_char(20, '!');
    for (std::map<std::string, char>::iterator it = m_separators.begin(); it != m_separators.end();
         ++it) {
        line_filter.setSeparator(it->first);
        line_filter.processSeparator(test_char);

        std::vector<char> compare_char(test_char.size(), it->second);
        for (int i = 0; i < start; ++i) {
            compare_char[i] = '!';
        }
        for (int i = end; i < test_char.size(); ++i) {
            compare_char[i] = '!';
        }

        EXPECT_EQ(compare_char, test_char);
    }
}

//! Test the separator generation with active filter from start to end of file (EOF)
TEST_F(LineFilterTest, processSeparatorActiveEOFTest)
{
    LineFilter line_filter("default_name");
    line_filter.setSeparators(&m_separators);

    int start = 2;
    int end = -1;
    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);

    std::vector<char> test_char(20, '!');
    for (std::map<std::string, char>::iterator it = m_separators.begin(); it != m_separators.end();
         ++it) {
        line_filter.setSeparator(it->first);
        line_filter.processSeparator(test_char);

        std::vector<char> compare_char(test_char.size(), it->second);
        for (int i = 0; i < start; i++) {
            compare_char[i] = '!';
        }

        EXPECT_EQ(compare_char, test_char);
    }
}

//! Test the separator generation with inactive filter from start to end of file (EOF)
TEST_F(LineFilterTest, processSeparatorInactiveEOFTest)
{
    LineFilter line_filter("default_name");
    line_filter.setSeparators(&m_separators);

    int start = 2;
    int end = -1;
    line_filter.setActive(false);
    line_filter.setStart(start);
    line_filter.setEnd(end);

    std::vector<char> test_char(20, '!');
    for (std::map<std::string, char>::iterator it = m_separators.begin(); it != m_separators.end();
         ++it) {
        line_filter.setSeparator(it->first);
        line_filter.processSeparator(test_char);
        std::vector<char> compare_char(test_char.size(), '!');
        EXPECT_EQ(compare_char, test_char);
    }
}

//! Test the separator generation with active filter in range
TEST_F(LineFilterTest, processTypeActiveRangeTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = 10;
    std::string type = "Data";

    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setType(type);

    std::vector<std::string> test_type(20, "");
    std::vector<std::string> compare_type(test_type.size(), type);
    for (int i = 0; i < start; ++i) {
        compare_type[i] = "";
    }
    for (int i = end; i < compare_type.size(); ++i) {
        compare_type[i] = "";
    }

    line_filter.processType(test_type);
    EXPECT_EQ(test_type, compare_type);
}

//! Test the separator generation with active filter from start to end of file (EOF)
TEST_F(LineFilterTest, processTypeActiveEOFTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = -1;
    std::string type = "Data";

    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setType(type);

    std::vector<std::string> test_type(20, "");
    std::vector<std::string> compare_type(test_type.size(), type);
    for (int i = 0; i < start; ++i) {
        compare_type[i] = "";
    }

    line_filter.processType(test_type);
    EXPECT_EQ(test_type, compare_type);
}

//! Test the type generation with inactive filter from start to end of file (EOF)
TEST_F(LineFilterTest, processTypeInactiveEOFTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = -1;
    std::string type = "Data";

    line_filter.setActive(false);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setType(type);

    std::vector<std::string> test_type(20, "");
    std::vector<std::string> compare_type(test_type.size(), "");

    line_filter.processType(test_type);
    EXPECT_EQ(test_type, compare_type);
}

//! Test the separator generation with active filter in range
TEST_F(LineFilterTest, processIgnoreActiveRangeTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = 10;
    std::string ignore_string = "#,@";
    std::vector<std::string> full{"#", "@"};
    std::vector<std::string> empty{};

    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setIgnoreString(ignore_string);

    std::vector<std::vector<std::string>> test_ignore(20, std::vector<std::string>());
    std::vector<std::vector<std::string>> compare_ignore(test_ignore.size(), full);

    for (int i = 0; i < start; ++i) {
        compare_ignore[i] = empty;
    }
    for (int i = end; i < compare_ignore.size(); ++i) {
        compare_ignore[i] = empty;
    }

    line_filter.processIgnore(test_ignore);
    EXPECT_EQ(test_ignore, compare_ignore);
}

//! Test the separator generation with active filter from start to end of file (EOF)
TEST_F(LineFilterTest, processIgnoreActiveEOFTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = -1;
    std::string ignore_string = "#,@";
    std::vector<std::string> full{"#", "@"};
    std::vector<std::string> empty{};

    line_filter.setActive(true);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setIgnoreString(ignore_string);

    std::vector<std::vector<std::string>> test_ignore(20, std::vector<std::string>());
    std::vector<std::vector<std::string>> compare_ignore(test_ignore.size(), full);

    for (int i = 0; i < start; ++i) {
        compare_ignore[i] = empty;
    }

    line_filter.processIgnore(test_ignore);
    EXPECT_EQ(test_ignore, compare_ignore);
}

//! Test the type generation with inactive filter from start to end of file (EOF)
TEST_F(LineFilterTest, processIgnoreInactiveEOFTest)
{
    LineFilter line_filter("default_name");

    int start = 2;
    int end = -1;
    std::string ignore_string = "#,@";
    std::vector<std::string> full{"#", "@"};
    std::vector<std::string> empty{};

    line_filter.setActive(false);
    line_filter.setStart(start);
    line_filter.setEnd(end);
    line_filter.setIgnoreString(ignore_string);

    std::vector<std::vector<std::string>> test_ignore(20, std::vector<std::string>());
    std::vector<std::vector<std::string>> compare_ignore(test_ignore.size(), empty);

    line_filter.processIgnore(test_ignore);
    EXPECT_EQ(test_ignore, compare_ignore);
}
