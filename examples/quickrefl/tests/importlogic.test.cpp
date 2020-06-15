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

#include "importfile.creator.h"
#include "importlinefilter.h"
#include "importlogic.h"

#include <chrono>
#include <cmath>
#include <map>
#include <string>
#include <vector>

using namespace DataImportLogic;

//! Test the data column item
class ImportLogicTest : public ::testing::Test
{
public:
    ImportLogicTest();
    ~ImportLogicTest();

    std::vector<CreateTestFiles::FileInput> generateFiles(char separator);
    std::vector<std::string> getPaths(const std::vector<CreateTestFiles::FileInput>& inputs);
    std::vector<double> stringToDouble(std::vector<std::string> input);

    ImportLogic import_logic;
    std::map<std::string, char> separators;
};

ImportLogicTest::ImportLogicTest() : ::testing::Test(), import_logic()
{
    // Set up the separators
    separators.insert(std::pair<std::string, char>("Space ( )", ' '));
    separators.insert(std::pair<std::string, char>("Comma (,)", ','));
    separators.insert(std::pair<std::string, char>("Semicolon (;)", ';'));
    separators.insert(std::pair<std::string, char>("Pipe (|)", '|'));
    separators.insert(std::pair<std::string, char>("Colon (:)", ':'));
    separators.insert(std::pair<std::string, char>("Tab", '\t'));
    separators.insert(std::pair<std::string, char>("Quote (\')", '\''));
    separators.insert(std::pair<std::string, char>("Apostrophe (\")", '\"'));
}

//! Convert the string vector to vector of double
std::vector<double> ImportLogicTest::stringToDouble(std::vector<std::string> input)
{
    std::vector<double> output;
    std::transform(input.begin(), input.end(), std::back_inserter(output),
                   [](const std::string& val) { return std::stod(val); });
    return output;
}

//! Produce 10 files of the given separator
std::vector<CreateTestFiles::FileInput> ImportLogicTest::generateFiles(char separator)
{
    std::vector<CreateTestFiles::FileInput> file_inputs;
    for (int i = 0; i < 10; ++i) {
        std::string path =
            "file_"
            + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(
                                 std::chrono::high_resolution_clock::now().time_since_epoch())
                                 .count())
            + ".txt";
        file_inputs.push_back(CreateTestFiles::writeDataFile(path, separator));
    }
    return file_inputs;
}

//! Extract the paths
std::vector<std::string>
ImportLogicTest::getPaths(const std::vector<CreateTestFiles::FileInput>& file_inputs)
{
    std::vector<std::string> path_vector;
    std::transform(
        file_inputs.begin(), file_inputs.end(), std::back_inserter(path_vector),
        [](const CreateTestFiles::FileInput& input) -> std::string { return input.path; });
    return path_vector;
}

ImportLogicTest::~ImportLogicTest() = default;

//! Test the add/remove filter
TEST_F(ImportLogicTest, lineFilterAddRemoveTest)
{
    auto filter_0 = import_logic.addLineFilter("Header");
    auto filter_1 = import_logic.addLineFilter("Data");
    auto filter_2 = import_logic.addLineFilter("Unit");
    auto filter_3 = import_logic.addLineFilter("Comment");

    EXPECT_EQ(4, import_logic.lineFilterOrder().size());
    import_logic.removeLineFilter(filter_1);
    EXPECT_EQ(3, import_logic.lineFilterOrder().size());
    import_logic.removeLineFilter(filter_2);
    EXPECT_EQ(2, import_logic.lineFilterOrder().size());

    filter_1 = import_logic.addLineFilter("Data");
    filter_2 = import_logic.addLineFilter("Unit");
    EXPECT_EQ(4, import_logic.lineFilterOrder().size());
}

//! Test the filter order
TEST_F(ImportLogicTest, lineFilterOrderTest)
{
    auto filter_0 = import_logic.addLineFilter("Header");
    auto filter_1 = import_logic.addLineFilter("Data");
    auto filter_2 = import_logic.addLineFilter("Unit");
    auto filter_3 = import_logic.addLineFilter("Comment");

    std::vector<LineFilter*> order{filter_0, filter_1, filter_2, filter_3};
    EXPECT_EQ(order, import_logic.lineFilterOrder());

    std::vector<LineFilter*> new_order{filter_3, filter_1, filter_2, filter_0};
    import_logic.setLineFilterOrder(new_order);
    EXPECT_EQ(new_order, import_logic.lineFilterOrder());
}

//! Test that the hasName method yields the right result
TEST_F(ImportLogicTest, hasNameTest)
{
    auto filter_0 = import_logic.addLineFilter("Header");
    auto filter_1 = import_logic.addLineFilter("Data");
    auto filter_2 = import_logic.addLineFilter("Unit");
    auto filter_3 = import_logic.addLineFilter("Comment");

    EXPECT_EQ(filter_0, import_logic.nameInFilters("Header"));
    EXPECT_EQ(filter_1, import_logic.nameInFilters("Data"));
    EXPECT_EQ(filter_2, import_logic.nameInFilters("Unit"));
    EXPECT_EQ(filter_3, import_logic.nameInFilters("Comment"));

    EXPECT_EQ(nullptr, import_logic.nameInFilters("Not_present"));
}

//! Test that the hasType method yields the right result
TEST_F(ImportLogicTest, hasTypeTest)
{
    auto filter_0 = import_logic.addLineFilter("Header");
    auto filter_1 = import_logic.addLineFilter("Data");
    auto filter_2 = import_logic.addLineFilter("Unit");
    auto filter_3 = import_logic.addLineFilter("Comment");

    filter_0->setType("Header");
    filter_1->setType("Data");
    filter_2->setType("Unit");
    filter_3->setType("Comment");

    EXPECT_EQ(filter_0, import_logic.typeInFilters("Header"));
    EXPECT_EQ(filter_1, import_logic.typeInFilters("Data"));
    EXPECT_EQ(filter_2, import_logic.typeInFilters("Unit"));
    EXPECT_EQ(filter_3, import_logic.typeInFilters("Comment"));

    EXPECT_EQ(nullptr, import_logic.typeInFilters("Not_present_type"));
}

//! Test that set files puts the right amount of files into the container
TEST_F(ImportLogicTest, setFilesTest)
{
    std::vector<CreateTestFiles::FileInput> file_inputs;
    for (std::map<std::string, char>::iterator it = separators.begin(); it != separators.end();
         ++it) {
        file_inputs = generateFiles(it->second);
        import_logic.setFiles(getPaths(file_inputs));
        EXPECT_EQ(file_inputs.size(), import_logic.getFinalOutput().keys().size());
        CreateTestFiles::removeFiles(file_inputs);
    }
}

//! Test the header processing
TEST_F(ImportLogicTest, lineFiltersHeaderTest)
{
    auto filter_0 = import_logic.addLineFilter("Header");

    filter_0->setType("Header");
    filter_0->setActive(true);

    std::vector<CreateTestFiles::FileInput> file_inputs;
    for (std::map<std::string, char>::iterator it = separators.begin(); it != separators.end();
         ++it) {
        file_inputs = generateFiles(it->second);
        import_logic.setFiles(getPaths(file_inputs));
        filter_0->setSeparator(it->first);

        int i = 0;
        for (const auto& file_input : file_inputs) {
            EXPECT_EQ(file_input.header, import_logic.getHeader(i++));
        }

        CreateTestFiles::removeFiles(file_inputs);
    }
}

//! Test the data processing
TEST_F(ImportLogicTest, lineFiltersDataTest)
{
    auto filter_1 = import_logic.addLineFilter("Data");

    filter_1->setType("Data");
    filter_1->setActive(true);
    filter_1->setStart(1);
    filter_1->setEnd(-1);

    std::vector<CreateTestFiles::FileInput> file_inputs;
    for (std::map<std::string, char>::iterator it = separators.begin(); it != separators.end();
         ++it) {
        file_inputs = generateFiles(it->second);
        import_logic.setFiles(getPaths(file_inputs));
        filter_1->setSeparator(it->first);

        int i = 0;
        for (const auto& file_input : file_inputs) {
            EXPECT_EQ(file_input.data, import_logic.getData(i++));
        }
        CreateTestFiles::removeFiles(file_inputs);
    }
}

//! Test the data processing
TEST_F(ImportLogicTest, totalFiltersResultTest)
{
    auto filter_0 = import_logic.addLineFilter("Header");
    auto filter_1 = import_logic.addLineFilter("Data");

    filter_0->setType("Header");
    filter_0->setActive(true);

    filter_1->setType("Data");
    filter_1->setActive(true);
    filter_1->setStart(1);
    filter_1->setEnd(-1);

    std::vector<CreateTestFiles::FileInput> file_inputs;
    for (std::map<std::string, char>::iterator it = separators.begin(); it != separators.end();
         ++it) {
        file_inputs = generateFiles(it->second);
        import_logic.setFiles(getPaths(file_inputs));
        filter_0->setSeparator(it->first);
        filter_1->setSeparator(it->first);
        auto output_items = import_logic.getFinalOutput();

        for (int i = 0; i < file_inputs.size(); ++i) {
            auto output_item = output_items[file_inputs[i].path];
            EXPECT_EQ(true, output_item->hasAxis());
            auto axis = stringToDouble(DataImportUtils::transpose(file_inputs[i].data).at(0));
            EXPECT_EQ(axis, output_item->axis());
            for (int j = 0; j < output_item->dataCount(); ++j) {
                auto data =
                    stringToDouble(DataImportUtils::transpose(file_inputs[i].data).at(j + 1));
                EXPECT_EQ(data, output_item->data(j));
            }
            CreateTestFiles::removeFiles(file_inputs);
        }
    }
}
