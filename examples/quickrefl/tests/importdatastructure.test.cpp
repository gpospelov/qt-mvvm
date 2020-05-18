// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"

#include "importdatacolumn.h"
#include "importdatastructure.h"
#include "importutils.h"

#include <cmath>
#include <string>
#include <vector>

using namespace DataImportLogic;

//! Test the data column item
class DataStructureTest : public ::testing::Test
{
public:
    ~DataStructureTest();
};

DataStructureTest::~DataStructureTest() = default;

//! Test default state after construction
TEST_F(DataStructureTest, contructor)
{
    DataStructure data_struct;
    std::vector<std::string> test_headers{"header_0", "header_1"};

    EXPECT_EQ(0, data_struct.rowCount());
    EXPECT_EQ(0, data_struct.columnCount());

    DataColumn* column_str = data_struct.column("hello");
    DataColumn* column_int = data_struct.column(0);
    const DataColumn* const_column_int = data_struct.column(0);

    EXPECT_EQ(nullptr, column_str);
    EXPECT_EQ(nullptr, column_int);
    EXPECT_EQ(nullptr, const_column_int);
}

//! Test set data with data only
TEST_F(DataStructureTest, setDataOnly)
{
    DataStructure data_struct;
    DataImportUtils::string_data test_data{{"1.", "2."}, {"1.", "2.", "3."}};
    data_struct.setData(test_data);

    EXPECT_EQ(3, data_struct.rowCount());
    EXPECT_EQ(2, data_struct.columnCount());

    DataColumn* column_0 = data_struct.column(0);
    DataColumn* column_1 = data_struct.column(1);

    EXPECT_NE(nullptr, column_0);
    EXPECT_NE(nullptr, column_1);
}

//! Test set data with data only and then set data with less columns
TEST_F(DataStructureTest, setDataOnlyLess)
{
    DataStructure data_struct;
    DataImportUtils::string_data test_data{{"1.", "2."}, {"1.", "2.", "3."}};
    data_struct.setData(test_data);

    EXPECT_EQ(3, data_struct.rowCount());
    EXPECT_EQ(2, data_struct.columnCount());

    DataImportUtils::string_data test_data_less{{"1.", "2.", "3."}};
    data_struct.setData(test_data_less);

    EXPECT_EQ(3, data_struct.rowCount());
    EXPECT_EQ(1, data_struct.columnCount());
}

//! Test set data with data and headers
TEST_F(DataStructureTest, setDataDataHeader)
{
    DataStructure data_struct;
    DataImportUtils::header_map test_header_map{{"header_0", 0}, {"header_1", 1}};
    DataImportUtils::string_data test_data{{"1.", "2."}, {"1.", "2.", "3."}};
    data_struct.setData(test_header_map, test_data);

    EXPECT_EQ(3, data_struct.rowCount());
    EXPECT_EQ(2, data_struct.columnCount());

    DataColumn* column_0 = data_struct.column(0);
    DataColumn* column_1 = data_struct.column(1);

    EXPECT_NE(nullptr, column_0);
    EXPECT_NE(nullptr, column_1);

    EXPECT_EQ("header_0", column_0->header());
    EXPECT_EQ("header_1", column_1->header());
}

//! Test set data with data and headers and then set data with one column less
TEST_F(DataStructureTest, setDataHeaderLess)
{
    DataStructure data_struct;
    DataImportUtils::header_map test_header_map{{"header_0", 0}, {"header_1", 1}};
    DataImportUtils::string_data test_data{{"1.", "2."}, {"1.", "2.", "3."}};
    data_struct.setData(test_header_map, test_data);

    EXPECT_EQ(3, data_struct.rowCount());
    EXPECT_EQ(2, data_struct.columnCount());

    DataImportUtils::header_map test_header_map_less{{"header_1", 0}};
    DataImportUtils::string_data test_data_less{{"1.", "2.", "3."}};
    data_struct.setData(test_header_map_less, test_data_less);

    EXPECT_EQ(3, data_struct.rowCount());
    EXPECT_EQ(1, data_struct.columnCount());
}
