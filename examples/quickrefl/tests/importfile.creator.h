// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importutils.h"
#include "test_utils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <QFile>

namespace CreateTestFiles
{

//! Generate the axis column
std::vector<double> generateAxisColumn(int rows)
{
    std::vector<double> output(rows);
    double gen_i = 0;
    std::generate(output.begin(), output.end(),
                  [&rows, &gen_i]() { return gen_i++ * (3 - 3e-1) / rows; });
    return output;
}

//! Generate the data column
std::vector<double> generateDataColumn(int rows)
{
    std::uniform_real_distribution<double> unif(1e2, 1e8);
    std::default_random_engine re;

    std::vector<double> output(rows);
    std::generate(output.begin(), output.end(), [&re, &unif]() { return unif(re); });
    return output;
}

//! Generate the data of number of columns
std::vector<std::vector<double>> generateData(int column, int rows)
{
    std::vector<std::vector<double>> data;

    if (column > 1)
        data.push_back(generateAxisColumn(rows));

    for (int i = 0; i < column - 1; ++i) {
        data.push_back(generateDataColumn(rows));
    }

    return DataImportUtils::transpose(data);
}

//! Generate the header of number of columns
std::map<std::string, int> generateHeader(int column)
{
    std::map<std::string, int> header;
    for (int i = 0; i < column; ++i) {
        header.insert(std::pair<std::string, int>(std::string{"Header_" + std::to_string(i)}, i));
    }
    return header;
}

//! Convert an input of doubles to sring
std::vector<std::vector<std::string>> convertToString(std::vector<std::vector<double>> input)
{
    std::vector<std::vector<std::string>> output(input.size(),
                                                 std::vector<std::string>(input[0].size(), ""));
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); ++j) {
            std::ostringstream ss;
            ss << input[i][j];
            output[i][j] = ss.str();
        }
    }
    return output;
}

//! Simple structure for input passing
struct FileInput {
public:
    std::string name;
    std::string path;

    char separator;
    int col_num;
    int row_num;

    std::vector<std::vector<std::string>> data;
    std::map<std::string, int> header;
};

//! Write a data file
FileInput writeDataFile(const std::string& name, char separator, int columns = 4, int rows = 100)
{
    std::string test_file_subfolder = "importtestfiles";
    std::string file_path;
    TestUtils::CreateTestDirectory(test_file_subfolder);
    file_path = TestUtils::TestFileName(test_file_subfolder, name);
    remove(file_path.c_str());

    // Prepare the buffer that will be used to compare test output
    FileInput file_input;
    file_input.name = name;
    file_input.path = file_path;

    file_input.separator = separator;
    file_input.col_num = columns;
    file_input.row_num = rows;

    file_input.data = convertToString(generateData(columns, rows));
    file_input.header = generateHeader(columns);

    std::ofstream file(file_path);
    // Write the header
    {
        std::string feed;
        for (const auto& header_item : file_input.header) {
            feed += header_item.first + separator;
        }
        feed.pop_back();
        feed += "\n";
        file << feed;
    }

    // Write the data
    for (const auto& data_row : file_input.data) {
        std::string feed;
        for (const auto& data_item : data_row) {
            feed += data_item + separator;
        }
        feed.pop_back();
        feed += "\n";
        file << feed;
    }

    file.close();
    return file_input;
}

//! Quick create comma separator file
FileInput createCommaCSVFile(const std::string& name)
{
    return writeDataFile(name, ',');
}

//! Quick create space separator file
FileInput createSpaceCSVFile(const std::string& name)
{
    return writeDataFile(name, ' ');
}

//! Quick create semicolumn separator file
FileInput createSemicolumnCSVFile(const std::string& name)
{
    return writeDataFile(name, ';');
}

//! Remove a file with the ollowing input
void removeFile(FileInput &file_input)
{
    QFile(QString::fromStdString(file_input.path)).remove();
}

//! Remove all files within the following vector
void removeFiles(std::vector<FileInput> file_inputs)
{
    for ( auto &file_input:file_inputs){
        removeFile(file_input);
    }
}

} // End of namespace CreateTestFiles