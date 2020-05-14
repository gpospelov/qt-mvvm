// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "importutils.h"
#include "test_utils.h"

#include <cmath>
#include <string>
#include <vector>

using namespace DataImportUtils;

//! Test the data column item
class DataImportUtilsTest : public ::testing::Test
{
public:
    ~DataImportUtilsTest();
};

DataImportUtilsTest::~DataImportUtilsTest() = default;

//! Test the spliting of a string to separator character
TEST_F(DataImportUtilsTest, splitStringTest)
{
    std::string input = "This is a test";
    std::vector<std::string> split_vec = split(input, ' ');
    std::vector<std::string> compare{"This", "is", "a", "test"};

    EXPECT_EQ(compare, split_vec);
}

//! Test the cleaning of a string after spliting
TEST_F(DataImportUtilsTest, cleanSplitStringTest)
{
    std::string input = "This,,is,a,,test";
    std::vector<std::string> split_vec = split(input, ',');
    std::vector<std::string> compare{"This", "", "is", "a", "", "test"};

    EXPECT_EQ(compare, split_vec);

    clean(split_vec);
    std::vector<std::string> compare_cleaned{"This", "is", "a", "test"};

    EXPECT_EQ(compare_cleaned, split_vec);
}

//! Erase all occurences of a substring within a string
TEST_F(DataImportUtilsTest, eraseAllSubStringTest)
{
    std::string input = "This is a test a";
    std::string to_erase = "a";
    eraseAllSubString(input, to_erase);
    std::string compare = "This is  test ";

    EXPECT_EQ(compare, input);
}

//! Erase a substring within a string
TEST_F(DataImportUtilsTest, eraseSubStringsTest)
{
    std::string input = "This is a test a";
    std::vector<std::string> to_erase{"is", "a"};
    eraseSubStrings(input, to_erase);
    std::string compare = "Th   test ";

    EXPECT_EQ(compare, input);
}

//! Test the transpose machinery
TEST_F(DataImportUtilsTest, transposeTest)
{
    string_data input{{"1", "2", "3"}, {"1", "2", "3"}, {"1", "2", "3"}, {"1", "2", "3"},
                      {"1", "2", "3"}, {"1", "2", "3"}, {"1", "2", "3"}, {"1", "2", "3"}};
    string_data compare{
        {"1", "1", "1", "1", "1", "1", "1", "1"},
        {"2", "2", "2", "2", "2", "2", "2", "2"},
        {"3", "3", "3", "3", "3", "3", "3", "3"},
    };

    string_data transposed = transpose(input);

    EXPECT_EQ(compare, transposed);
}
