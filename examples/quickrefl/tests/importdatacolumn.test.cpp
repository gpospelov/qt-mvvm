// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "importdatacolumn.h"
#include "test_utils.h"

#include <cmath>
#include <string>
#include <vector>

using namespace DataImportLogic;

//! Test the data column item
class DataColumnTest : public ::testing::Test
{
public:
    ~DataColumnTest();
};

DataColumnTest::~DataColumnTest() = default;

//! Test default constructor
TEST_F(DataColumnTest, defaultContructor)
{
    DataColumn column;

    EXPECT_EQ("No Name", column.name());
    EXPECT_EQ("Intensity", column.type());
    EXPECT_EQ("", column.header());
    EXPECT_EQ("a.u.", column.unit());
    EXPECT_EQ(1., column.multiplier());
    EXPECT_EQ(true, column.values().empty());
    EXPECT_EQ(0, column.rowCount());
}

//! Test header constructor
TEST_F(DataColumnTest, headerContructor)
{
    DataColumn column("Default");

    EXPECT_EQ("No Name", column.name());
    EXPECT_EQ("Intensity", column.type());
    EXPECT_EQ("Default", column.header());
    EXPECT_EQ("a.u.", column.unit());
    EXPECT_EQ(1., column.multiplier());
    EXPECT_EQ(true, column.values().empty());
}

//! Test the setters and getters for attributes
TEST_F(DataColumnTest, setterGetterAttr)
{
    DataColumn column;

    std::string name = "default_name";
    std::string type = "Axis";
    std::string header = "default_header";
    std::string unit = "deg";
    double multiplier = 2.;

    column.setName(name);
    column.setType(type);
    column.setHeader(header);
    column.setUnit(unit);
    column.setMultiplier(multiplier);

    EXPECT_EQ(name, column.name());
    EXPECT_EQ(type, column.type());
    EXPECT_EQ(header, column.header());
    EXPECT_EQ(unit, column.unit());
    EXPECT_EQ(multiplier, column.multiplier());
}

//! Test setters and getters for data string input
TEST_F(DataColumnTest, setterGetterDataString)
{
    DataColumn column;

    std::vector<std::string> string_vec{"1.", "2.", "3.", "4.", "5."};
    std::vector<double> simple_output{1, 2, 3, 4, 5};
    std::vector<double> final_output{2, 4, 6, 8, 10};
    double multiplier = 2.;

    column.setValues(string_vec);
    column.setMultiplier(multiplier);

    EXPECT_EQ(simple_output, column.values());
    EXPECT_EQ(final_output, column.finalValues());
    EXPECT_EQ(simple_output[3], column.value(3));
    EXPECT_EQ(final_output[3], column.finalValue(3));
}

//! Test setters and getters for data double input
TEST_F(DataColumnTest, setterGetterDataDouble)
{
    DataColumn column;

    std::vector<double> simple_output{1, 2, 3, 4, 5};
    std::vector<double> final_output{2, 4, 6, 8, 10};
    double multiplier = 2.;

    column.setValues(simple_output);
    column.setMultiplier(multiplier);

    EXPECT_EQ(simple_output, column.values());
    EXPECT_EQ(final_output, column.finalValues());
    EXPECT_EQ(simple_output[3], column.value(3));
    EXPECT_EQ(final_output[3], column.finalValue(3));
}

//! Test the std::nan handing
TEST_F(DataColumnTest, setterGetterDataStringNan)
{
    DataColumn column;

    std::vector<std::string> string_vec{"1.", "nan", "3.", "4.", "5."};
    double multiplier = 2.;

    column.setValues(string_vec);
    column.setMultiplier(multiplier);

    EXPECT_TRUE(std::isnan(column.value(1)));
    EXPECT_FALSE(std::isnan(column.value(0)));
}

//! Test clearValues
TEST_F(DataColumnTest, clearValues)
{
    DataColumn column;

    std::vector<std::string> string_vec{"1.", "nan", "3.", "4.", "5."};

    column.setValues(string_vec);

    EXPECT_EQ(5, column.rowCount());

    column.clearValues();

    EXPECT_EQ(0, column.rowCount());
}

//! Test the copy constructor
TEST_F(DataColumnTest, ctor)
{
    DataColumn column;

    std::string name = "default_name";
    std::string type = "Axis";
    std::string header = "default_header";
    std::string unit = "deg";
    double multiplier = 2.;
    std::vector<std::string> string_vec{"1.", "2.", "3.", "4.", "5."};
    std::vector<double> simple_output{1, 2, 3, 4, 5};
    std::vector<double> final_output{2, 4, 6, 8, 10};

    column.setName(name);
    column.setType(type);
    column.setHeader(header);
    column.setUnit(unit);
    column.setMultiplier(multiplier);
    column.setValues(string_vec);

    DataColumn other_column = DataColumn(column);

    EXPECT_EQ(name, other_column.name());
    EXPECT_EQ(type, other_column.type());
    EXPECT_EQ(header, other_column.header());
    EXPECT_EQ(unit, other_column.unit());
    EXPECT_EQ(multiplier, other_column.multiplier());
    EXPECT_EQ(simple_output, other_column.values());
    EXPECT_EQ(final_output, other_column.finalValues());
    EXPECT_EQ(simple_output[3], other_column.value(3));
    EXPECT_EQ(final_output[3], other_column.finalValue(3));
}
